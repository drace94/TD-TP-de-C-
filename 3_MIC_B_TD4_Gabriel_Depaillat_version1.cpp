#include <iostream>
using namespace std;

//-------------------------------------------TD1,2,3-------------------------------------------------------------------

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

//-------------------------------------------------TD4----------------------------------------------------------------------------

template <typename T> class vector_gen {
	private :
		int dim;
		T* elements;
	public :
		vector_gen() {
			dim = 0;
			elements = NULL;                               //constructeur sans argument
		}
		vector_gen(int taille) {
			dim = taille;
			elements = new T[taille];			//constructeur avec une taille
		}
		vector_gen(int taille, T arg) {
			dim = taille;
			elements = new T[taille];			//constructeur avec une taille qui initialise
			for (int i = 0; i<taille; i++) {		// tout à nombre arg
				elements[i] = arg;
			}
		}
		vector_gen(const vector_gen<T> & other) {
			dim = other.dim;
			elements = new T[dim];				//constructeur copie
			for (int i=0;i<dim;i++) {
				elements[i] = other.elements[i];
			}
		}

		void put() {
			if (elements == NULL) {cout << "Tableau vide" << endl;}
			else {
				for (int i=0;i<dim;i++) {
					cout << " | " << elements[i];			//Je le remets pour les tests, il sert a afficher le
				}							//vecteur. Pas besoin de get donc je ne le remets pas
			cout << " | " << endl;
			}
		}
		
		T & operator[] (int indice) {
			if (indice < dim) {
				return elements[indice];
			} else {cout << "Out of range" << endl; exit(30);}
		}

		T operator[] (int indice) const {
			if (indice < dim) {
				return elements[indice];
			} else {cout << "Out of range" << endl; exit(30);}
		}

		vector_gen<T> & operator= (const vector_gen<T> & v) {
			if (dim == v.dim) {
			elements = v.elements;
			} else {cout << "Erreur de dimension lors de l'affectation" << endl;exit(20);}
			return (*this);
		}

		vector_gen<T> & operator += (const vector_gen<T> & v) {
			int i;
			if (dim != v.dim) {
				cout << "Dimensions incompatibles" << endl;
				exit(50);
			} else {
				for (i=0;i<dim;i++) elements[i]+=v.elements[i];
			}
			return (*this);
		}

		vector_gen<T> operator+ (const vector_gen<T> & v) {
			if (dim != v.dim) {
				cout << "Error" << endl;
				exit(50);						//à l'interieur de la classe sinon
			} else {							//le compilateur ne comprend pas le <T>
				vector_gen<T> v2(dim);
				v2.elements = new T[dim];
				for (int i=0;i<v.dim;i++) v2[i]=elements[i]+v[i];
			return v2;
			}
		}
		
		template <typename Y> friend ostream & operator << (ostream & flux, const vector_gen<Y> & v);
		template <typename Y> friend istream & operator >> (istream & is, vector_gen<Y> & v);
};

template <typename Y> ostream & operator << (ostream & flux, vector_gen<Y> const & v){
  flux << "[";
  for (int i=0; i<v.dim-1; i++){
    flux << v.elements[i] << " ";
  }
    flux << v.elements[v.dim-1];
    flux << "]" << endl;
    return flux;
}

template <typename Y> istream & operator >> (istream & is, vector_gen <Y> & v) {
    if (v.dim==0){
      cout << "vecteur non initialisé"; exit(-2);}
    else {
      for (int i=0; i<v.dim;i++){
    cout << "Une valeur svp : ";
    cin >> v.elements[i];
      }
    }
    return (is);
}

int main(void) {
	vector_gen<float> v1,v2(3);
	vector_gen<char> v3(4,'f');
	char c;
	v3[2] = 'k';
	v3[1] = 'p';
	cout << "v3 ="<< endl;
	v3.put();
	c = v3[2];							//test de l'opérateur "[]"
	cout << "v3[2] = " << c << endl;				//ça marche
	cout << "----------------------------------------" << endl;
	vector_gen<float> v4(4,2.0);
	vector_gen<float> v5(4);
	//v3 = v4;							//test de l'opérateur "=" et ca compile pas à cause des types (ok)
	v5 = v4;							//test de l'opérateur "=" dans de bonnes conditions et ça marche
	cout << "v5 ="<< endl;
	v5.put();
	cout << "----------------------------------------" << endl;
	v4 += v5;							//test de l'opérateur "+=" dans de bonnes conditions (ok)
	cout << "v4 = " << endl;
	v4.put();
	cout << "----------------------------------------" << endl;
	cout << "v6 = v4 + v5 ="<< endl;
	v4.put();
	cout << "+"<< endl;
	v5.put();
	vector_gen<float> v6(4);
	v6 = v4 + v5;							//test de l'opérateur "+" dans de bonnes conditions (ok)
	cout << "v6 ="<< endl;
	v6.put();
	cout << "----------------------------------------" << endl;
	cout << "v6 = " << v6 << endl;					//test de la surcharge de << (ok)
	cout << "----------------------------------------" << endl;
	cin >> v6;							//test de la surcharge de >> (ok)
	cout << "v6 = " << v6 << endl;
	return (0);
}
