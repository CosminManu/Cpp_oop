// 2021_motocilete.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include<fstream>
#include<vector>

#define _copy(dest, src) strcpy_s(dest, strlen(src) + 1, src)

using namespace std;

class Motocicleta 
{
	const int id;
protected:
	char* producator;
	string model;
	double capacitate;
public:
	Motocicleta()
		:id(10001)
	{
		this->producator = new char[strlen("necunoscut") + 1];
		_copy(this->producator, "necunoscut");
		this->model = "necunoscut";
		this->capacitate = 0;
	}

	Motocicleta(const char* _prod, string _mod, double _cap)
		:id(20002)
	{
		if (_prod != nullptr) {
			this->producator = new char[strlen(_prod) + 1];
			_copy(this->producator, _prod);
		}
		this->model = _mod;
		this->capacitate = _cap;
	}

	Motocicleta(const Motocicleta& m) 
		:id(m.id)
	{
		this->producator = new char[strlen(m.producator) + 1];
		_copy(this->producator, m.producator);
		this->model = m.model;
		this->capacitate = m.capacitate;
	}

	Motocicleta& operator=(const Motocicleta& m)
	{
		if (this != &m) {
			if (this->producator != nullptr) {
				delete[] this->producator;
			}
			this->producator = new char[strlen(m.producator) + 1];
			_copy(this->producator, m.producator);
			this->model = m.model;
			this->capacitate = m.capacitate;
			return *this;
		}
	}

	~Motocicleta()
	{
		if (this->producator != nullptr) {
			delete[] this->producator;
		}
	}

	char* getProducator()
	{
		return this->producator;
	}

	void setProducator(const char* prod) {
		if (prod != nullptr) {
			this->producator = new char[strlen(prod) + 1];
			_copy(this->producator, prod);
		}
	}

	void adaugaModel(string mod) {
		this->model = this->model + " " + mod;
	}

	void adaugaModel(string mod, string mod2) {
		this->model = this->model + " " + mod + " " + mod2;
	}

	string getModel() {
		return this->model;
	}

	//pt serializare ofstream => include fstream
	void serializare(string NumeFisier)
	{
		ofstream f(NumeFisier, ios::out | ios::binary);
		//va trebui sa facem conversie datelor catre char*

		//pentru char*	-- 2 write (lung si text)
		int l1 = strlen(this->producator);
		f.write((char*)&l1, sizeof(l1));
		f.write(this->producator, l1 + 1);

		//pentru string	-- 2 write (lung size() si text c_str()=>transf in char*)
		int l2 = this->model.size();
		f.write((char*)&l2, sizeof(l2));
		f.write(this->model.c_str(), l2 + 1);

		f.write((char*)&this->capacitate, sizeof(this->capacitate));	//cast la char* cu adresa elem &
		
		f.close();
	}

	explicit operator double()
	{
		return this->capacitate;

	}
};

class MotocicElectrica : public Motocicleta
{
public:
	//op = apeleaza pe cel din clasa baza
	MotocicElectrica& operator=(const Motocicleta& m)
	{
		Motocicleta::operator=(m);
		return *this;
	}
};

class Parcare
{
	vector<Motocicleta> vector;
public:

	void adaugaMoto(Motocicleta& m) {
		vector.push_back(m);
	}
};

int main()
{
	Motocicleta m1;
	Motocicleta m2("Yamaha", "300YL", 0.5);
	Motocicleta m3 = m2;

	cout << m2.getProducator() << endl;
	m3.setProducator("Suzuki");
	cout << m3.getProducator() << endl;

	m2.adaugaModel("KTM");
	cout << m2.getModel() << endl;

	m3.serializare("binar.dat");

	MotocicElectrica me1;
	me1 = m2;

	vector<Motocicleta> vec;
	vec.push_back(m1);
	vec.push_back(m1);
	vec.push_back(m2);

	double x = (double)m3;
	cout << "Capacitate motor: " << x << endl;

}


