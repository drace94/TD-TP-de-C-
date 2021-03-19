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
		void get();
		int getdim() const {return dim;};
		vector operator + (const vector& v2);
		vector operator += (const vector& v2);

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

vector vector::operator+ (const vector& v2) {
	if ((*this).getdim() != v2.getdim()) {
		cout << "Error" << endl;
		exit(50);
	} else {
		vector v((*this).getdim());
		v.elements = new float[dim];
		for (int i=0;i<v.getdim();i++) {
			v[i] = (*this)[i]+v2[i];
		}
		return v;
	}
}

vector vector::operator+= (const vector& v2) {
	if ((*this).getdim() != (*this).getdim()) {
		cout << "Error" << endl;
		exit(50);
	} else {
		for (int i=0;i<v2.getdim();i++) {
			(*this)[i] += v2[i];
		}
		return (*this);
	}
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
	vector p6(3);
	p6.get();
	cout << "p6[1] = " << p6[1] << endl;
	p6[1] = 3.6;
	float f = p6[1];
	cout << "f = " << f << endl;
	vector p5(3);
	//p5 = p6;                                                             // test de l'erreur
	p5[1] = 4.1;
	cout << "p5[1] = " << p5[1] << " et p6[1] = " << p6[1] << endl;
	p5.put();
	p6.put();
	vector p7 = p5+p6;
	p7.put();
	p6.put();
	p7 += p6;
	p7.put();
	return(0);
}
