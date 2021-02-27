// handout 5


#include <iostream>
#include <string>
using namespace std;

class Cartus
{
private:
	string producator;
	int nrTotalPagini;
public:
	int getNrTotalPagini() {
		return nrTotalPagini;
	}
};


class Imprimanta
{
private:
	const int serialNumber = 0;
	char* producator;
	int nrPaginiPrintate;
	static string tipImprimanta;
	Cartus cartus;

	//1. Modificati constructorul implicit din clasa Imprimanta de mai jos
	//acesta va initializa producatorul cu un sir de caractere vid ("")
	//si numarul de pagini printate cu 0
	Imprimanta()
		:serialNumber(1)
	{
		producator = new char[2];
		strcpy_s(producator, 2, "");	// (prod, 2, "")

		nrPaginiPrintate = 0;
	}

	//2. Modificati constructorul cu 3 parametri: serialNumber, producator, nrPaginiPrintate
//acesta va initializa cele 3 atribute cu valorile primite
//atributul constant nu va mai fi initializat la definire
//constructorul implicit va initializa acest atribut cu 1

	Imprimanta(int serialNumber, char* producator, int nrPaginiPrintate)
		:serialNumber(serialNumber)
	{
		if (producator != nullptr) {
			this->producator = new char[strlen(producator) + 1];
			strcpy_s(this->producator, strlen(producator) + 1, producator);
		}
		this->nrPaginiPrintate = nrPaginiPrintate;
	}

	//3. Adaugati un destructor in clasa pentru a dezaloca
//campul(urile) alocate dinamic
	~Imprimanta() {
		if (producator != nullptr) {
			delete[]producator;
			producator = nullptr;		// "Test" != null
		}
	}

	//4. Adaugati clasei un constructor de copiere astfel incat
//sa se realizeze o copie in profunzime (deep copy) a obiectelor
//se va realiza si copierea campului constant
	/*const int serialNumber = 0;
	char* producator;
	int nrPaginiPrintate;
	static string tipImprimanta;*/

	Imprimanta(const Imprimanta& source)
		:serialNumber(source.serialNumber), nrPaginiPrintate(source.nrPaginiPrintate)
	{
		this->producator = new char[strlen(source.producator) + 1];
		strcpy_s(this->producator, strlen(source.producator) + 1, source.producator);
	}

	//5. Modificati supraincarcarea pentru operator=
//aceasta va realiza o copie in profunzime (deep copy) a obiectelor
//operatorul accepta apeluri in cascada
	/*const int serialNumber = 0;
	char* producator;
	int nrPaginiPrintate;
	static string tipImprimanta;*/

	Imprimanta operator=(const Imprimanta& source)
	{
		//if (this->producator != nullptr) {
		//	delete[] this->producator;			// pot sa am scris deja in mem la producator
		//}

		this->nrPaginiPrintate = source.nrPaginiPrintate;
		if (source.producator != nullptr) {
			this->producator = new char[strlen(source.producator) + 1];
			strcpy_s(this->producator, strlen(source.producator) + 1, source.producator);
		}
		else {
			this->producator = nullptr;
		}
		return *this;
	}

	static string getTipImprimanta()
	{
		return tipImprimanta;
	}

	static void setTipImprimanta(string tipImprimanta)
	{
		Imprimanta::tipImprimanta = tipImprimanta;
	}
	//7. Modificati metodele de acces pentru campul static
//astfel incat acestea sa permita modificarea si obtinerea valorii acestui camp
	//static string tipImprimanta;

	//8. Modificati metoda getTotalPaginiPerProducator pentru a returna numarul total de pagini
//printate de toate imprimantele din vectorul de imprimante primit ca parametru
//care sunt produse de producatorul primit drept parametru
//De ex daca avem 3 imprimante: "Dell" - 120 de pagini, "HP" - 150 de pagini, "Dell" - 170 de pagini
//functia va returna 290 de pagini daca primeste ca parametru producatorul "Dell"
//si 150 de pagini daca primeste ca parametru producatorul "HP"
//pentru orice alt producator functia va returna 0
	//const int serialNumber = 0;
	//char* producator;
	//int nrPaginiPrintate;
	//static string tipImprimanta;
	//Cartus cartus;

	static long getTotalPaginiPerProducator(Imprimanta* imprimante, int nrImprimante, char* producator)
	{
		long S = 0;
		//imprimante = new Imprimanta[nrImprimante]; 
		//S = imprimante[0].nrPaginiPrintate;
		for (int i = 0; i < nrImprimante; i++) {
			if (strcmp(imprimante[i].producator, producator) == 0) {
				S = S + imprimante[i].nrPaginiPrintate;
			}
		}
		if (S == 0) {
			return 0;
		}
		else return S;

	}

	//9. Modelati o relatie de compunere intre clasa Cartus si clasa Imprimanta
//astfel incat sa reiasa faptul ca Imprimanta are (foloseste) un Cartus
//Modificati metoda setCartus astfel incat sa puteti schimba cartusul curent al imprimantei
//cu cel primit drept parametru si metoda getCartus pentru a returna cartusul curent

	void setCartus(Cartus c)
	{
		Imprimanta::cartus = c;
	}

	Cartus getCartus()
	{
		return Imprimanta::cartus;
	}

	//10. Modificati metoda getNumarPaginiRamase astfel incat sa returneze numarul de pagini
//pe care imprimanta respectiva la mai poate printa avand in vedere ca stim 
//cate pagini se pot printa maxim cu cartusul curent si cate pagini au fost printate pana acum
//functia nu poate returna o valoare negativa, asa ca daca numarul curent de pagini il
//depaseste pe cel maxim, va returna 0
	//string producator;
	//int nrTotalPagini;

	//const int serialNumber = 0;
	//char* producator;
	//int nrPaginiPrintate;
	//static string tipImprimanta;

	/*class Cartus
	{
	private:
		string producator;
		int nrTotalPagini;
	public:
		int getNrTotalPagini() {
			return nrTotalPagini;
		}
	}cartus1;*/	// ob de tip Cartus vizibil doar in clasa parinte

	int getNumarPaginiRamase()
	{
		int total = Imprimanta::cartus.getNrTotalPagini();
		int pagRamase = total - nrPaginiPrintate;
		if (pagRamase < 0) {
			return 0;
		}
		else return pagRamase;
	}

};
//6. Initializati membrul static tipImprimanta cu valoarea "Cerneala"
string Imprimanta::tipImprimanta = "Cerneala";

//Imprimanta::Cartus cartus;  inaccesibil de la 173

//ATENTIE!!!
//Sunt punctate doar solutiile originale si individuale
//Orice incercare de frauda va duce la pierderea intregului punctaj de la seminar
//Signatura functiilor nu se poate modifica, doar continului lor

//1. Modificati constructorul implicit din clasa Imprimanta de mai sus
//acesta va initializa producatorul cu un sir de caractere vid ("")
//si numarul de pagini printate cu 0

//2. Modificati constructorul cu 3 parametri: serialNumber, producator, nrPaginiPrintate
//acesta va initializa cele 3 atribute cu valorile primite
//atributul constant nu va mai fi initializat la definire
//constructorul implicit va initializa acest atribut cu 1

//3. Adaugati un destructor in clasa pentru a dezaloca
//campul(urile) alocate dinamic

//4. Adaugati clasei un constructor de copiere astfel incat
//sa se realizeze o copie in profunzime (deep copy) a obiectelor
//se va realiza si copierea campului constant

//5. Modificati supraincarcarea pentru operator=
//aceasta va realiza o copie in profunzime (deep copy) a obiectelor
//operatorul accepta apeluri in cascada

//6. Initializati membrul static tipImprimanta cu valoarea "Cerneala"

//7. Modificati metodele de acces pentru campul static
//astfel incat acestea sa permita modificarea si obtinerea valorii acestui camp

//8. Modificati metoda getTotalPaginiPerProducator pentru a returna numarul total de pagini
//printate de toate imprimantele din vectorul de imprimante primit ca parametru
//care sunt produse de producatorul primit drept parametru
//De ex daca avem 3 imprimante: "Dell" - 120 de pagini, "HP" - 150 de pagini, "Dell" - 170 de pagini
//functia va returna 290 de pagini daca primeste ca parametru producatorul "Dell"
//si 150 de pagini daca primeste ca parametru producatorul "HP"
//pentru orice alt producator functia va returna 0

//9. Modelati o relatie de compunere intre clasa Cartus si clasa Imprimanta
//astfel incat sa reiasa faptul ca Imprimanta are (foloseste) un Cartus
//Modificati metoda setCartus astfel incat sa puteti schimba cartusul curent al imprimantei
//cu cel primit drept parametru si metoda getCartus pentru a returna cartusul curent

//10. Modificati metoda getNumarPaginiRamase astfel incat sa returneze numarul de pagini
//pe care imprimanta respectiva la mai poate printa avand in vedere ca stim 
//cate pagini se pot printa maxim cu cartusul curent si cate pagini au fost printate pana acum
//functia nu poate returna o valoare negativa, asa ca daca numarul curent de pagini il
//depaseste pe cel maxim, va returna 0

int main()
{
	//pt apeluri lasa private doar atributele din Imprimanta

		//char* producator = new char[6];			// apel 5/ oper'='
		//strcpy_s(producator, 6, "Canon");
		//Imprimanta m(12345, producator, 250);
		//Imprimanta n;

		/*char* producator1 = new char[5];
		strcpy_s(producator1, 5, "Dell");
		char* producator2 = new char[3];
		strcpy_s(producator2, 3, "HP");

		Imprimanta x(45678, producator1, 1500);
		Imprimanta y(12345, producator2, 1200);
		Imprimanta z;
		z = y = x;*/


		//Cartus c;									// apel 10/
		//c.producator = "Auchan";
		//c.nrTotalPagini = 500;

		//char* producator1 = new char[5];
		//strcpy_s(producator1, 5, "Dell");
		//Imprimanta x(123, producator1, 150);
		//x.setCartus(c);
		//int result = x.getNumarPaginiRamase();

		//char* producator2 = new char[3];
		//strcpy_s(producator2, 3, "HP");
		//Imprimanta y(456, producator2, 600);
		//y.setCartus(c);
		//result = y.getNumarPaginiRamase();		// apel 10/


		/*char* producator1 = new char[5];			// apel 8/
		strcpy_s(producator1, 5, "Dell");
		Imprimanta i1(1, producator1, 120);

		char* producator2 = new char[3];
		strcpy_s(producator2, 3, "HP");
		Imprimanta i2(2, producator2, 250);

		char* producator3 = new char[5];
		strcpy_s(producator3, 5, "Dell");
		Imprimanta i3(3, producator3, 240)
			;
		char* producator4 = new char[3];
		strcpy_s(producator4, 3, "HP");
		Imprimanta i4(4, producator4, 190);

		char* producator5 = new char[6];
		strcpy_s(producator5, 6, "Canon");
		Imprimanta i5(5, producator5, 100);
		Imprimanta v[] = { i1, i2, i3, i4, i5 };

		char* producator6 = new char[6];
		strcpy_s(producator6, 6, "Delly");
		if (Imprimanta::getTotalPaginiPerProducator(v, 5, producator6) == 0) {
			cout << "bine";
		}
		else if (Imprimanta::getTotalPaginiPerProducator(v, 5, producator3) == 360) {
			cout << "bine";
		}
		else if (Imprimanta::getTotalPaginiPerProducator(v, 5, producator4) == 440) {
			cout << "bine";
		}
		else if (Imprimanta::getTotalPaginiPerProducator(v, 5, producator5) == 100) {
			cout << "bine";
		}
		else cout << "rahat";*/
}