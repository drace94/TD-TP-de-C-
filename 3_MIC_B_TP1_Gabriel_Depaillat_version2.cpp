#include <iostream>
#include <list>
#include <typeinfo>
#include <exception>

using namespace std;

class MyException : public std::runtime_error {
	public:
		MyException(const char * msg) : std::runtime_error(msg) {}
		virtual const char* what() const noexcept {
    		return std::runtime_error::what();
  	}
};

class Coloriable{
	protected :
		string couleur;
	public :
		Coloriable(string coul){couleur=coul;}
		string getCouleur(){return couleur;}
		void setCouleur(string coul){couleur=coul;}
};

class Figure {
	public :
		Figure () {
			compteur++;
		}
		virtual float perimetre() = 0;
		virtual void afficherCaracteristiques() = 0;
		static int nb_figures() {
			return compteur;
		}
	protected :
		static int compteur;
};

class Polygone : public Figure {
	protected :
		int nbCotes;
	public :
		Polygone(int cote) {
			nbCotes = cote;
		}
		void afficherCaracteristiques() {
			cout << "Le polygone a " << nbCotes << " coté(s)" << endl;
		}
};

class Rectangle : public Polygone {
	protected :
		float largeur;
		float longueur;
		// int nbCotes;
	public :
		Rectangle(float lar, float lon):Polygone(4) {
			longueur=lon;
			largeur=lar;
		}

		float getlargeur() {
			return largeur;
		}
		float getlongueur () {
			return longueur;
		}
		void changelargeur (float largeur) {
			this->largeur = largeur;
		}
		void changelongueur (float longueur) {
			this->longueur = longueur;
		}

		void afficherCaracteristiques() {
			cout << "Ce rectangle a 4 cotes avec une largeur de " << largeur << " et une longueur de " << longueur << endl;
		}

		float perimetre () {
			return 2*largeur + 2*longueur;
		}
};

class Carre : public Rectangle {
	public :
		Carre(float longueur):Rectangle(longueur,longueur) {};
		void afficherCaracteristiques() {
			cout << "Ce carre a 4 cotes avec une longueur de " << longueur << endl;
		}
};

class TriangleEquilateral : public Polygone {
	protected :
		float longueur;
	public :
		TriangleEquilateral(float lon) : Polygone(3) {
			longueur = lon;
		}

		float perimetre () {
			return 3*longueur;
		}

		void afficherCaracteristiques() {
			cout << "Ce triangle a 3 cotes avec une longueur de " << longueur << endl;
		}

		void setlongueur (float lon) {
			longueur = lon;
		}

		float getlongueur () {
			return longueur;
		}
};

class Cercle : public Figure, public Coloriable {
	protected :
		float rayon;
		// string couleur;
	public :
		Cercle(float r, string coul):Coloriable(coul) {
			rayon = r;
		}

		float perimetre() {
			return 3.1415*2*rayon;
		}
		
		void setrayon(float r) {
			rayon = r;
		}
	
		float getrayon () {
			return rayon;
		}

		void afficherCaracteristiques() {
			cout << "Ce cercle a un rayon de " << rayon << endl;
		}
};

class Cellule{
	protected :
		Figure * element;
		Cellule * suivante;
	public :
		Cellule(Figure * ele) {
			element = ele;
			suivante = NULL;
		}
		friend class File;
};

class File{
	private : 
		int nb_elements;
		Cellule * premiere;
		Cellule * derniere;
	public :
		File() {
			nb_elements = 0;
			premiere = NULL;
			derniere = NULL;
		}

		void insertion (Figure * fig) {
			Cellule * nv = new Cellule(fig);
			if (premiere == NULL) {
				premiere = nv;
				derniere = nv;
			} else {
				derniere->suivante=nv;
				derniere=nv;
			}
			nb_elements++;
		}
		
		void suppression() {
			if (premiere == NULL) {
				throw MyException("File vide");
			} else {
				premiere=premiere->suivante;
				nb_elements-=1;
			}
		}

		bool file_vide() {
			if (premiere==NULL) {
				return true;
			} else {
				return false;
			}
		}

		Figure * premier_element() {
			if (file_vide()) {throw MyException("File vide");}
			else {return premiere->element;}
		}

		int nbr_elements() {
			return nb_elements;
		}
};

int Figure::compteur = 0;

int main(void) {
	// on peut pas créer de Polygone à cause de périmetre
	/*
	Figure *tab[3];
	tab[0] = new Carre(3);
	tab[1] = new Cercle(2,"red");
	tab[2] = new TriangleEquilateral(1.5);
	cout << "------------------------------------" << endl;
	for (int i=0; i<3; i++) {
		tab[i]->afficherCaracteristiques();
		cout << "Perimetre : " << tab[i]->perimetre() << endl;
		cout << "------------------------------------" << endl;
	}
	cout << Figure::nb_figures() << " figures créées au total" << endl;
	*/

    	File file;
    	file.insertion(new Rectangle(2.,3.));
    	file.insertion(new Carre(2.));
    	file.insertion(new TriangleEquilateral(2.));
    	file.insertion(new Cercle(2.,"red"));
    	file.insertion(new Cercle(2.,"blue"));
    	cout << "La file contient " << file.nbr_elements() << " figure(s)." << endl;
    
    	while (not(file.file_vide())){
        	(file.premier_element())->afficherCaracteristiques();
		cout << "Il a un périmètre de : " << (file.premier_element())->perimetre();
		if (typeid(*(file.premier_element()))==typeid(Cercle)) {
			//cout << " ici";
			//Worst way 
			//cout << " et il est de couleur " << ((Cercle*)file.premier_element())->getCouleur();
			//Better way 
			//cout << " et il est de couleur " << dynamic_cast<Cercle*>(file.premier_element())->getCouleur();
			//Best way is the worst way
		}
		if (Cercle* cer = dynamic_cast<Cercle*>(file.premier_element())) {
				cout << " et il est de couleur " << cer->getCouleur();
		}
		//La meilleure méthode était de mettre un code dans AfficherCaracteristiques
        	cout << endl;
        	file.suppression();
    	}
    
    	cout << "La file contient " << file.nbr_elements() << " figure(s)." << endl;
	// On va essayer de lever l'exception.
	file.suppression();
	return(0);
}
