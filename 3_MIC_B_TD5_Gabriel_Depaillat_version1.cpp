#include <iostream>
using namespace std;

#define DIM_ERREUR_INDIC 1
#define DIM_ERREUR_AFFECT 2
#define DIM_ERREUR_ADD 3

#define TAB_VIDE 4

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
		
		void put();						// permet l'affichage
		void get();
		int getdim() const {return dim;};
		vector & operator += (const vector & v);

		float & operator[] (int indice) {
			if (indice < dim) {
				return elements[indice];
			} else {throw DIM_ERREUR_INDIC;}
		}
		float operator[] (int indice) const {
			if (indice < dim) {
				return elements[indice];
			} else {throw DIM_ERREUR_INDIC;}
		}
		vector & operator= (const vector & v) {
			if (dim == v.dim) {
			elements = v.elements;
			} else {throw DIM_ERREUR_AFFECT;}
			return (*this);
		}
		
		friend vector multiplication (float f, vector & v);
};

vector & vector::operator += (const vector & v) {
    int i;
    if (dim != v.dim){
        throw DIM_ERREUR_ADD;
    } else {
        for (i=0;i<dim;i++) elements[i]+=v.elements[i];
    }
    return (*this);
}

vector operator + (const vector & v1,const vector & v2) {
    vector v_tmp(v1);
    v_tmp+=v2;
    return v_tmp;
}

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
	if (elements == NULL) {throw TAB_VIDE;}
	else {
		for (int i=0;i<dim;i++) {
			cout << "Veuillez insérer l'élément n°" << i << " : ";
			cin >> elements[i];
		}
	}
}

vector multiplication (float f, vector & v) {
	vector p(v.dim);
	for (int i=0;i<v.dim;i++) {
		p.elements[i] = f*v.elements[i];
		//p1[i] = f*v[i];
	}
	return p;
}

class matrice{
	public:
		vector *tab[10];		//j'ai pris pour base le TD2, donc il n'y a pas vecteur_intel
						//d'implémenté mais ça ne change pas grand chose

		matrice() {
			for (int i=0;i<10;i++) {
				this->tab[i] = new vector;
			}
		}

		matrice(int taille_vect) {
			for (int i=0;i<10;i++) {
				this->tab[i] = new vector(taille_vect); //constructeur qui initialise tout à 0
			}
		}

		matrice(int taille_vect, float f) {
			for (int i=0;i<10;i++) {
				this->tab[i] = new vector(taille_vect,f); //constructeur qui initialise tout à f
			}
		}
		
		// il pourrait être intéressant de faire un get();

		void put();

};

void matrice::put() {
	if (this->tab[0] == NULL) {
		throw TAB_VIDE;
	} else {
		for (int i=0;i<10;i++) {
			(*(this->tab[i])).put();
		}
	}
}

int main(void) {
	try {
		vector p1(3,3.5);
		vector p2(2,3.0);
		//float k = p1[5];
		//cout << k << endl;
		
		//p2 += p1;
		//vector p3;
		//p3.get();                     //test de toutes les exceptions (ok)
		
		//--------------------------------------------------------------------------------------

		p1.put();
		vector p3(3);			//il doit être compatible sinon "=" fait une exception
		p3 = multiplication(3.0,p1);
		p3.put();

		//---------------------------------------------------------------------------------------

		matrice mat(3,4.4);
		mat.put();		
	}
	catch (int e) {
		if (e == DIM_ERREUR_INDIC) {
			cout << "Erreur de dimensionnement lors d'une opération d'indicage" << endl;
		} else {
		if (e == TAB_VIDE) {
			cout << "Erreur le tableau est vide" << endl;
		} else {
		if (e == DIM_ERREUR_ADD) {
			cout << "Erreur de dimensionnement lors d'une addition" << endl;
		} else {
		if (e == DIM_ERREUR_AFFECT) {
			cout << "Erreur de dimensionnement lors d'une affectation" << endl;
		} 
		}}}
	}
	return(0);
}
