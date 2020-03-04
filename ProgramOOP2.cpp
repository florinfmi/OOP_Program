/*Tema 7. matrice de numere complexe reprezentate ca tablouri bidimensionale

Se dau urmatoarele clase :
-Clasa Complex(float re, im)
- Matrice(Complex **v) – clasa abstracta
- Matrice_oarecare(int lin, int col) : Matrice
- Matrice_patratica(int dim) : Matrice

Clasele derivate trebuie sa contina cel puțin constructori parametrizati prin
care sa se evidentieze transmiterea parametrilor catre constructorul din clasa
de baza, destructori si o metoda care sa verifice daca o matrice triunghiulara
este diagonala.Pentru matricile patratice, functia de afisare sa conțină și
determinantul acestora.
*/
#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
using namespace std;

ifstream f("date.txt");

class Complex
{
protected:
	float re, im;
public:
	Complex();
	Complex(const Complex&);
	Complex(float, float);
	friend istream& operator >>(istream&, Complex&);
	friend ifstream& operator >>(ifstream&, Complex&);
	friend ostream& operator <<(ostream&, Complex);
	Complex& operator = (const Complex&);
	Complex operator + (Complex);
	Complex operator * (Complex);
	Complex operator - (Complex);
	Complex operator / (Complex);
	double modul(Complex);
	bool operator ==(Complex);
	bool operator !=(Complex);
	bool operator <(Complex);
	friend class Matrice;
	~Complex() {};

};

Complex::Complex()
{
	re = 0;
	im = 0;
}

Complex::Complex(const Complex& ob)
{
	re = ob.re;
	im = ob.im;
}

Complex::Complex(float r, float i)
{
	re = r;
	im = i;
}

ifstream& operator >>(ifstream& in, Complex& ob)
{
	in >> ob.re >> ob.im;
	return in;
}

istream& operator >>(istream& in, Complex& ob)
{
	in >> ob.re >> ob.im;
	return in;
}

ostream& operator <<(ostream& out, Complex ob)
{
	out << ob.re << " " << ob.im << "i ";
	return out;
}


Complex& Complex::operator =(const Complex& ob)
{
	if (this != &ob)
	{
		re = ob.re;
		im = ob.im;
	}
	return *this;
}

Complex Complex::operator +(Complex ob)
{
	Complex p;
	p.re = re + ob.re;
	p.im = im + ob.im;
	return p;
}

Complex Complex::operator * (Complex ob)
{
	Complex p;
	p.re = re * ob.re - im * ob.im;
	p.im = re * ob.im + ob.re * im;
	return p;
}

Complex Complex::operator - (Complex ob)
{
	Complex p;
	p.re = re - ob.re;
	p.im = im - ob.im;
	return p;
}

Complex Complex::operator / (Complex ob)
{
	try {
		if (!ob.re && !ob.im)
			throw "Impartire la 0";
		Complex p;
		p.re = (re * ob.re + im * ob.im) / (re * re + im * im);
		p.im = (re * ob.im - ob.re * im) / (re * re + im * im);
		return p;
	}
	catch (const char* h)
	{
		cout << h << endl;
	}

}

double Complex::modul(Complex ob)
{
	return sqrt(pow(ob.re, 2) + pow(ob.im, 2));
}

bool Complex::operator==(Complex ob)
{
	if (re == ob.re && im == ob.im)
		return true;
	return false;
}

bool Complex::operator!=(Complex ob)
{
	if (re != ob.re && im != ob.im)
		return true;
	return false;
}

bool Complex::operator<(Complex ob)
{
	return modul(*this) < modul(ob);
}

class Matrice
{
protected:
	Complex **v;

public:
	Matrice();
	Matrice(int, int);
	virtual void citire() = 0;
	virtual void afisare() = 0;
	bool TriunghiularaDiagonala(int, int);
};
Matrice::Matrice()
{
	v = NULL;
}

Matrice::Matrice(int l, int c)
{
	v = new Complex*[l];
	for (int i = 0; i < l; i++)
		v[i] = new Complex[c];

}

bool Matrice::TriunghiularaDiagonala(int lin, int col)
{
	Complex zero(0, 0);
	int i, j;
	if (v[0][0] != zero) // verific mai intai diagonala principala
	{
		for (i = 0; i < lin; i++)
			for(j=0;j<col;j++)
			if (v[i][j] != zero && i!=j) //verific daca exista vreun element diferit de
				return false;            //zero inafara diagonalei principale

	}
	else //altfel verific daca e diagonala dupa cea secundara
	{
	 for (i = 0; i < lin; i++)
		for (j = 0; j < col; j++)
			if (v[i][j] != zero && j != (col - i-1))//verific daca exista vreun element
				return false;                      //diferit de zero inafara diagonalei
	}
	return true;
}

class Matrice_oarecare : public Matrice
{
	int l, c;
public:
	Matrice_oarecare():Matrice () // v se initializeaza cu null
	{                            //la apelul constructorului de baza al bazei
		l = 0;
		c = 0;
	}
	Matrice_oarecare(int lin = 0, int col = 0) :Matrice()
	{
		l = lin;
		c = col;
		v = new Complex*[l];
		for (int i = 0; i < l; i++)
			v[i] = new Complex[c];

	}
	Matrice_oarecare(const Matrice_oarecare&);

	Matrice_oarecare operator =(const Matrice_oarecare);
	void citire();
	void afisare();

	~Matrice_oarecare()
	{
		for (int i = 0; i < l; i++)
			delete[]v[i];
		delete[]v;
	}
};

Matrice_oarecare::Matrice_oarecare(const Matrice_oarecare &ob)
{
	int i, j;

	l = ob.l;
	c = ob.c;

	v = new Complex*[l];
	for (j = 0; j < l; j++)
		v[j] = new Complex[c];

	for (i = 0; i < l; i++)
		for (j = 0; j < c; j++)
			v[i][j] = ob.v[i][j];
}

Matrice_oarecare Matrice_oarecare::operator=(const Matrice_oarecare ob)
{
	if (this != &ob)
	{
		int i, j;
		l = ob.l;
		c = ob.c;

		v = new Complex*[l];
		for (j = 0; j < l; j++)
			v[j] = new Complex[c];

		for (i = 0; i < l; i++)
			for (j = 0; j < c; j++)
				v[i][j] = ob.v[i][j];
	}

	return *this;
}

ifstream& operator >>(ifstream& in, Matrice_oarecare & m)
{
	m.citire();
	return in;
}

void Matrice_oarecare::citire()
{
	f >> l;
	f >> c;
	v = new Complex*[l];
	for (int i = 0; i<l; i++)
		v[i] = new Complex[c];

	for (int i = 0; i < l; i++)
		for (int j = 0; j < c; j++)
			f >> v[i][j];

}
ostream& operator <<(ostream& out, Matrice_oarecare& m)
{
	m.afisare();
	return out;
}
void Matrice_oarecare::afisare()
{
	int i, j;
	for (i = 0; i < l; i++)
	{
		cout << endl;
		for (j = 0; j < c; j++)
				cout << v[i][j] << " ";
	}
	cout << endl;
}



class Matrice_patratica:public Matrice
{
	int dim;
public:

   Matrice_patratica():Matrice()
	{
		dim = 0;
	}
	Matrice_patratica(int d):Matrice()
	{
		dim = d;
		v = new Complex*[dim];
		for (int i = 0; i<dim; i++)
			v[i] = new Complex[dim];
	}
	Matrice_patratica(const Matrice_patratica&);

	friend ifstream& operator >>(ifstream&, Matrice_patratica&);
	friend ostream& operator <<(ostream&, Matrice_patratica&);

	void citire();
	void afisare();

	Matrice_patratica operator *(Matrice_patratica);
	Matrice_patratica operator *(Complex);
	Matrice_patratica operator =(const Matrice_patratica);
	Matrice_patratica Minor(int ,int);



	Complex Determinant();

	~Matrice_patratica()
	{
		for (int i = 0; i < dim; i++)
			delete[]v[i];
		delete[]v;
	}

};

Matrice_patratica::Matrice_patratica(const Matrice_patratica &ob)
{
	int i, j;

	dim = ob.dim;

	v = new Complex*[dim];
	for (j = 0; j < dim; j++)
		v[j] = new Complex[dim];

	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
			v[i][j] = ob.v[i][j];
}

ifstream & operator>>(ifstream & in, Matrice_patratica& m)
{
	m.citire();
	return in;
}

void Matrice_patratica::citire()
{

	f >> dim;
	v = new Complex*[dim];
	for (int i = 0; i<dim; i++)
		v[i] = new Complex[dim];
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			f >> v[i][j];
}

ostream& operator <<(ostream& out , Matrice_patratica& m)
{
	m.afisare();
	return out;
}

void Matrice_patratica::afisare()
{
	int i, j;

	if (TriunghiularaDiagonala(dim, dim))
		cout << "Matricea triunghiulara este diagonala.";
	else
		cout << "NU este triunghiulara.";
	cout << endl << endl;

	cout <<"Deter="<< Determinant() << "\n";

	for (i = 0; i<dim; i++)
	{
		cout << endl;
		for (j = 0; j < dim; j++)
			cout << v[i][j] << " ";

	}
	cout << endl << endl;
}

Matrice_patratica Matrice_patratica::operator*(Matrice_patratica m)
{
	int i, j, k;
	Matrice_patratica p(dim);

	for (i = 0; i < p.dim; i++)
		for (j = 0; j < p.dim; j++)
			for (k = 0; k < dim; k++)
				p.v[i][j] = p.v[i][j] + v[i][k] * m.v[k][j];
	return p;
}

Matrice_patratica Matrice_patratica::operator*(Complex a)
{
	int i, j;

	Matrice_patratica p(dim);

	for (i = 0; i < p.dim; i++)
		for (j = 0; j < p.dim; j++)
			p.v[i][j] = a * v[i][j];
	return p;
}

Matrice_patratica Matrice_patratica::operator=(const Matrice_patratica ob)
{
	if (this != &ob)
	{
		int i, j;
		dim = ob.dim;

		v = new Complex*[dim];
		for (j = 0; j < dim; j++)
			v[j] = new Complex[dim];

		for (i = 0; i < dim; i++)
			for (j = 0; j < dim; j++)
				v[i][j] = ob.v[i][j];
	}

	return *this;
}

Matrice_patratica Matrice_patratica::Minor(int linie, int coloana)
{
	Matrice_patratica p(dim - 1);

	int i, j, c = 0, l = 0;

	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)
			if (j != coloana && i != linie)
			{
				p.v[l][c] = v[i][j];
				c++;
				if (c == p.dim)
				{
					c = 0;
					l++;
				}
			}

	return p;

}

Complex Matrice_patratica::Determinant()
{     //calculez determinantul pentru matrice mai mare de 2 dezvoltand dupa prima linie

	int i;
	Complex det;
	Matrice_patratica min;
	if (dim == 1)
	{
		det = v[0][0];
	}
	if (dim == 2)
	{
		det = v[0][0] * v[1][1] - v[0][1] * v[1][0];
	}
	if (dim >= 3)
	{
		for (i = 0; i < dim; i++)
		{
			min = Minor(0, i);
			if (i % 2)
				det = det + v[0][i] * min.Determinant();
			else
				det = det - v[0][i] * min.Determinant();
		}
	}
	return det;

}

int main()
{
	Matrice_patratica a,b,c;
	a.citire();
	b.citire();
	c.citire();
	a.afisare();
	b.afisare();
	c.afisare();
    return 0;
}

