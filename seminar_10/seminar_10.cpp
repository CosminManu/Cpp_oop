#include <iostream>
using namespace std;

class Persoana {
private:
	string nume;
	string prenume;
	int an_nastere;
public:
	Persoana()
	{
		nume = "";
		prenume = "";
		an_nastere = 1900;
	}

	Persoana(string nume, string prenume, int an_nastere)
	{
		this->an_nastere = an_nastere;
		this->nume = nume;
		this->prenume = prenume;
	}

	virtual float venit() = 0;
};

class Comparabil	// interfata(contine doar met virtuale pure)
{
public:
	virtual int compara(Comparabil*) = 0;

};

class Student : public Persoana, public Comparabil
{
private:
	const int nr_matricol;
	float bursa;
	static int nr_stud;
public:
	Student() :nr_matricol(++nr_stud)
	{
		bursa = 0;
	}

	Student(string nume, string prenume, int an_nastere, float bursa)
		:nr_matricol(++nr_stud), Persoana(nume,prenume,an_nastere)
	{
		this->bursa = bursa;
	}

	float venit() override		// overr ne ajuta la supradef
	{
		return bursa;
	}

	int compara(Comparabil* c)
	{
		Student* s = (Student*)c;
		if (this->nr_matricol < s->nr_matricol)
		{
			return -1;
		}
		else if (this->nr_matricol > s->nr_matricol) {
			return 1;
		}
		else return 0;
	}
};

int Student::nr_stud = 0;

class Angajat : public Persoana
{
private:
	int an_vechime;
	float salariu;
public:
	Angajat()
	{
		an_vechime = 0;
		salariu = 0;
	}

	// nu e oblig un constr sa aiba toti param (an vech)

	Angajat(string nume, string prenume, int an_nastere, float salariu)
		:Persoana(nume,prenume,an_nastere)
	{
		this->salariu = salariu;
		an_vechime = 0;
	}

	float venit()override
	{
		return salariu;
	}

};


class Pensionar :public Persoana, public Comparabil
{
private:
	float pensie;
public:
	Pensionar()
	{
		pensie = 0;
	}

	Pensionar(string nume, string prenume, int an_nastere, float pensie)
		:Persoana(nume, prenume, an_nastere)
	{
		this->pensie = pensie;
	}

	float venit()override
	{
		return pensie;
	}

	int compara(Comparabil* c) 
	{
		Pensionar* p = (Pensionar*)c;
		if (this->pensie < p->pensie)
		{
			return -1;
		}
		else if (this->pensie > p->pensie) {
			return 1;
		}
		else return 0;
	}
};




int main()
{
	Persoana* p = nullptr;
	Student s("Ionescu", "Ion", 2000, 700);
	Student a("Andrei", "Vasile", 1977, 2500);
	Pensionar pen("Andrei", "Balan", 1969, 1500);

	int x = 0;
	cout << "valoare = ";
	cin >> x;

	if (x % 2 == 0)
	{
		p = &s;		// pot salva in pointer pers adresa de stud
	}
	else p = &a;

	cout << p->venit() << endl;		//program config (alege la exec in fct de val data de mn lui p)
	
	Angajat b("Andrei", "Ioana", 1979, 2500);
	
	Persoana** v = new Persoana * [3];
	v[0] = &s;
	v[1] = &a;
	v[2] = &pen;

	float buget_familie = 0;
	for (int i = 0; i < 3; i++) {
		buget_familie = buget_familie + v[i]->venit();
	}
	delete[]v;
	cout << "Bugetul familiei " << buget_familie << endl;
	
	Student ss;
	cout << s.compara(&ss) << endl;


}