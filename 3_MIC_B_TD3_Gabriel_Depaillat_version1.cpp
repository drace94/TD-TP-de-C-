#include <iostream>
using namespace std;

class vector {
	protected :
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
		void get();
		int getdim() const {return dim;};
		//vector operator + (const vector& v2);
		vector & operator += (const vector& v);

		float & operator[] (int indice) {
			if (indice < dim) {
				return elements[indice];
			} else {cout << "Out of range" << endl; exit(30);}
		}
		float operator[] (int indice) const {
			if (indice < dim) {
				return elements[indice];
			} else {cout << "Out of range" << endl; exit(30);}
		}
		vector & operator= (const vector & v) {
			if (dim == v.dim) {
			elements = v.elements;
			} else {cout << "Erreur de dimension lors de l'affectation" << endl;exit(20);}
			return (*this);
		}
};

class vector_intel : public vector {
	public :
		vector_intel() : vector() {}
		vector_intel(int taille) : vector(taille) {}
		vector_intel(int taille, float nombre) : vector(taille,nombre) {}
		vector_intel(const vector_intel &v) : vector(v) {}
		//vector_intel operator+ (const vector_intel & v);
		vector_intel & operator += (const vector_intel & v);
		vector_intel & operator = (const vector_intel & v) {
			if (dim != v.dim) {
				dim = v.dim;
				delete[] elements;
				elements=new float(dim);
				for (int i=0; i < dim;i++) elements[i]=v.elements[i];		// nouvel opérateur "=" pour gérer le pb de taille
			}
			return (*this);
		}
};

vector & vector::operator+= (const vector & v) {
	int i;
	if (dim != v.dim) {
		cout << "Dimensions incompatibles" << endl;
		exit(50);
	} else {
		for (i=0;i<dim;i++) elements[i]+=v.elements[i];
	}
	return *this;
}

vector operator + (const vector & v1, const vector & v2) {
	vector v_tmp(v1);
	v_tmp+=v2;
	return v_tmp;
}

vector_intel & vector_intel::operator+= (const vector_intel & v) {
	if (dim >= v.dim) {
		for (int i=0;i<v.dim;i++) elements[i] += v.elements[i];
	} else if (dim < v.dim) {
		float * aux = elements;
		dim = v.dim;
		elements = new float(v.dim);
		for (int i=0;i<dim;i++) elements[i] = aux[i] + v.elements[i];
		for (int i=dim;i<v.dim;i++) elements[i] = v.elements[i];
	}										// Nouvel opérateur du TD3 qui est intelligent (testé)
	return (*this);
}

vector_intel operator + (const vector_intel & v1, const vector_intel & v2) {
	vector_intel v_tmp(v1);								// Nouvel opérateur du TD3 qui a besoin de "=" qui marche pas
	v_tmp += v2;
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
	if (elements == NULL) {cout << "Tableau vide, impossible de le remplir. Utilisez un autre constructeur" << endl;}
	else {
		for (int i=0;i<dim;i++) {
			cout << "Veuillez insérer l'élément n°" << i << " : ";
			cin >> elements[i];
		}
	}
}

int main(void) {
	vector_intel p1(4,2);
	vector_intel p2(2,1);
	p1.put();
	p2.put();
	cout << "Opération +=" << endl;
	p2 += p1;
	p2.put();
	cout << "Opération +" << endl;
	vector_intel p3(2);
	p3 = p1+p2;
	p3.put();
	return(0);
}
