#include <iostream>
using namespace std;

class vector {
	private :
		int dim;                                                //taille du tableau
		float* elements;					//tableau
	public :
		vector() {
			dim = 0;
			elements = NULL;                               //constructeur sans argument
		}
		vector(int taille) {
			dim = taille;
			elements = new float[taille];			//constructeur avec une taille qui initialise
			for (int i = 0;i<taille;i++) {			//tout à 0.0
				elements[i] = 0.0;
			}
		}
		vector(int taille, float nombre) {
			dim = taille;
			elements = new float[taille];			//constructeur avec une taille qui initialise
			for (int i = 0; i<taille; i++) {		// tout à nombre (argument)
				elements[i] = nombre;
			}
		}
		vector(const vector & other) {
			dim = other.dim;
			elements = new float[dim];			//constructeur copie
			for (int i=0;i<dim;i++) {
				elements[i] = other.elements[i];
			}
		}
		~vector(){						//destructeur qui désalloue la mémoire
			dim = 0;					//et qui réinitialise la dimension
			delete [] elements;
		}
		void put();						// permet l'affichage
		void get();						// permet la saisie au clavier
};

void vector::put() {
	if (elements == NULL) {cout << "Tableau vide" << endl;}
	else {
		for (int i=0;i<dim;i++) {
			cout << " | " << elements[i];
		}
	cout << " | " << endl;
	}
}

void vector::get() {
	if (elements == NULL) {cout << "Tableau vide, impossible de le remplir. Utilisez un autre constructeur" << endl;}
	else {
		for (int i=0;i<dim;i++) {
			cout << "Veuillez insérer l'élément n°" << i << " : ";
			cin >> elements[i];
		}
	}
}

int main(void) {
	vector p1;
	vector p2(4);
	vector p3(5,1.2);
	vector p4(p3);                         //utilisation des 4 constructeurs
	p1.put();
	p2.put();
	p3.put();				//affichage des 4 vecteurs
	p4.put();
	vector p5;				//création de 2 nouveaux vecteurs
	vector p6(3);
	p5.get();

	p6.get();				//remplissage des 2 nouveaux vecteurs
	p6.put();				//Affichage du 2eme seulement car le premier est de taille 0
	p6.get();
	p6.put();
	return(0);
}
