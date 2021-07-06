// 2021_cabStomato.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define _copy(dest, src) strcpy_s(dest, strlen(src) + 1, src)

using namespace std;

class CabinetStoma
{
	char* adresa;
	char* denumire;
	int numarMedici;
	int oraInchidere[2];
public:
	static string tipCab;
	const int numar;

	CabinetStoma()
		:numar(11001)
	{
		this->adresa = new char[strlen("Necunoscut") + 1];
		_copy(this->adresa, "Necunoscut");

		this->denumire = new char[strlen("Stomato") + 1];
		_copy(this->denumire, "Stomato");

		this->numarMedici = 0;
		for (int i = 0; i < 2; i++) {
			this->oraInchidere[i] = 0;
		}
	}

	CabinetStoma(const char* _adresa, const char* _den, int _nr, int ora[2])
		:numar(22002)
	{
		if (_adresa != nullptr) {
			this->adresa = new char[strlen(_adresa) + 1];
			_copy(this->adresa, _adresa);
		}

		if (_den != nullptr) {
			this->denumire = new char[strlen(_den) + 1];
			_copy(this->denumire, _den);
		}

		this->numarMedici = _nr;
		for (int i = 0; i < 2; i++) {
			this->oraInchidere[i] = ora[i];
		}
	}

	CabinetStoma(const CabinetStoma& c)
		:numar(c.numar)
	{
		if (c.denumire != nullptr) {
			this->denumire = new char[strlen(c.denumire) + 1];
			_copy(this->denumire, c.denumire);
		}

		if (c.adresa != nullptr) {
			this->adresa = new char[strlen(c.adresa) + 1];
			_copy(this->adresa, c.adresa);
		}

		this->numarMedici = c.numarMedici;
		for (int i = 0; i < 2; i++) {
			this->oraInchidere[i] = c.oraInchidere[i];
		}
	}

	~CabinetStoma()
	{
		if (this->denumire != nullptr) {
			delete[] this->denumire;
		}
		if (this->adresa != nullptr) {
			delete[] this->adresa;
		}	
	}

	void setOraInchid(int ora[2])
	{
		if (ora[0] > 0 && ora[0] <= 24 && ora[1] > 0 && ora[1] <= 24) {
			for (int i = 0; i < 2; i++) {
				this->oraInchidere[i] = ora[i];
			}
		}
	}

	int* getOra() {
		return this->oraInchidere;
	}

	char* getDenumire()
	{
		return this->denumire;
	}

	friend istream& operator>>(istream& in, CabinetStoma& c);
	friend ostream& operator<<(ostream& os, const CabinetStoma& c);

};

//char* adresa;
//char* denumire;
//int numarMedici;
//int oraInchidere[2];
//const int numar;
ostream& operator<<(ostream& os, const CabinetStoma& c)
{
	os << "Adresa cabinet: "<< c.adresa << endl;
	os << "Denumire: "<< c.denumire << endl;
	os << "Numar Medici: "<< c.numarMedici << endl;
	os << "Ora inchidere: (ora/min) ";
	for (int i = 0; i < 2; i++) {
		 os << c.oraInchidere[i] << ":";
	}
	cout << endl;
	os << "Numar: " << c.numar << endl;
	return os;
}

istream& operator>>(istream& in, CabinetStoma& c)
{
	if (c.denumire != nullptr) {
		delete[] c.denumire;
	}
	if (c.adresa != nullptr) {
		delete[] c.adresa;
	}

	cout << "adresa cabinet: ";
	in >> ws;
	char aux[250];
	in.getline(aux, 249);
	c.adresa = new char[strlen(aux) + 1];
	_copy(c.adresa, aux);

	cout << "Denumire: ";
	in >> ws;
	char aux1[50];
	in.getline(aux1, 49);
	c.denumire = new char[strlen(aux1) + 1];
	_copy(c.denumire, aux1);

	cout << "Numar medici: ";
	in >> c.numarMedici;

	cout << "Ora inchidere: (ora/min) ";
	for (int i = 0; i < 2; i++) {
		in >> c.oraInchidere[i];
	}
	return in;
}

string CabinetStoma::tipCab = "Cabinet Stomatologic";

int main()
{
	int ora[2] = { 20, 0 };
	CabinetStoma c1;
	CabinetStoma c3("Bld BIzuintei 80", "DentalMed", 3, ora);
	CabinetStoma c2 = c3;

	cout << c3.getDenumire() << endl;

	cout << "Ora inchidere: ";
	for (int i = 0; i < 2; i++) {
		cout << c3.getOra()[i] << ":";
	}
	cout << endl;

	cout << c2 << endl << endl;

	CabinetStoma c4;
	cin >> c4;
	cout << c4 << endl << endl;

}

