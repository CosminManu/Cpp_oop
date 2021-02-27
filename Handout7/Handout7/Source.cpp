#include <iostream>
#include <string>
#include<iomanip>
using namespace std;

class TrainRoute
{
private:
	string departure;
	string destination;
	char* trainCode;

public:
	//1. Modificati constructorul cu parametri din clasa TrainRoute pentru a initializa
//statia de plecare, statia de sosire si codul trenului
	TrainRoute(string departure, string destination, const char* trainCode)
	{
		this->departure = departure;
		this->destination = destination;
		if (trainCode != nullptr) 
		{
			this->trainCode = new char[strlen(trainCode) + 1];
			strcpy_s(this->trainCode, strlen(trainCode) + 1, trainCode);
		}
	}

	//2. Respectati "regula celor 3" in cadrul clasei TrainRoute
		/*string departure;
		string destination;
		char* trainCode;*/
	TrainRoute(const TrainRoute& t)
	{
		departure = t.departure;
		destination = t.destination;
		if (t.trainCode != nullptr) {
			trainCode = new char[strlen(t.trainCode) + 1];
			strcpy_s(this->trainCode, strlen(t.trainCode) + 1, t.trainCode);
		}
	}
	TrainRoute operator=(const TrainRoute& t)
	{
		if (trainCode != nullptr) {
			delete[] trainCode;
		}
		departure = t.departure;
		destination = t.destination;
		if (t.trainCode != nullptr) {
			trainCode = new char[strlen(t.trainCode) + 1];
			strcpy_s(trainCode, strlen(t.trainCode) + 1, t.trainCode);
		}
		return *this;
	}

	virtual ~TrainRoute()
	{
		if (trainCode != nullptr) {
			delete[] trainCode;
		}
	}

	virtual int totalWeight()
	{
		return 100;
	}

	friend ostream& operator<<(ostream&, TrainRoute);
	friend istream& operator>>(istream&, TrainRoute&);
};


class FreightTrainRoute : public TrainRoute
{
private:
	int nbOfWagons;
	float* weigthPerWagon;

public:
	//4. Modificati constructorul implicit al clasei FreightTrainRoute
//acesta va initializa numarul de vagoane cu 0 si vectorul de greutati cu nullptr
//statia de plecare si destinatia vor fi initializate cu un sir vid
//codul trenului va fi "Necunoscut"
	FreightTrainRoute()
		:TrainRoute("", "", "Necunoscut")
	{
		nbOfWagons = 0;
		weigthPerWagon = nullptr;
	}

	//5. Modificati constructorului cu parametri al clasei FreightTrainRoute
//astfel incat sa initializeze corect statia de plecare, destinatia si codul trenului
//numarul de vagoane si vectorul de greutati vor ramane 0, respectiv nullptr
//clasa TrainRoute nu se poate modifica pentru a contine constructor implicit
	FreightTrainRoute(string departure, string destination, const char* trainCode)
		:TrainRoute(departure, destination, trainCode)
	{
		/*nbOfWagons = 0;
		weigthPerWagon = nullptr;*/
	}

	//6. Modificati metoda setWeigth astfel incat sa se poata modifica
//vectorul de greutati si numarul de vagoane
	/*int nbOfWagons;
	float* weigthPerWagon;*/
	void setWeigth(int nbOfWagons, float* weightPerWagon)
	{
		if (weightPerWagon != nullptr && nbOfWagons > 0)
		{
			this->nbOfWagons = nbOfWagons;
			this->weigthPerWagon = new float[nbOfWagons];
			for (int i = 0; i < nbOfWagons; i++)
			{
				this->weigthPerWagon[i] = weightPerWagon[i];
			}
		}
	}
	//9. Supradefiniti metoda totalWeight in clasa FreightTrainRoute
//astfel incat sa returneze greutatea totala a trenului ca intreg
//prin trunchiere (se ignora zecimalele rezultatului final)
	/*int nbOfWagons;
	float* weigthPerWagon;*/
	int totalWeight()
	{
		float S = 0.0f;
		for (int i = 0; i < nbOfWagons; i++)
		{
			S = S + weigthPerWagon[i];
		}
		return (int)S;
	}


	//7. Aplicati "regula celor 3" si in clasa derivata
	/*int nbOfWagons;
	float* weigthPerWagon;*/
	FreightTrainRoute(const FreightTrainRoute& aux)
		:TrainRoute(aux)
	{
		this->nbOfWagons = aux.nbOfWagons;
		this->weigthPerWagon = new float[aux.nbOfWagons];
		for (int i = 0; i < aux.nbOfWagons; i++)
		{
			this->weigthPerWagon[i] = aux.weigthPerWagon[i];
		}
	}
	~FreightTrainRoute()
	{
		if (weigthPerWagon != nullptr)
		{
			delete[] weigthPerWagon;
			weigthPerWagon = nullptr;
		}
	}
	FreightTrainRoute operator=(const FreightTrainRoute& aux)
	{
		TrainRoute::operator=(aux);
		if (weigthPerWagon != nullptr)
		{
			delete[] weigthPerWagon;
			weigthPerWagon = nullptr;
		}
		this->nbOfWagons = aux.nbOfWagons;
		this->weigthPerWagon = new float[aux.nbOfWagons];
		for (int i = 0; i < aux.nbOfWagons; i++)
		{
			this->weigthPerWagon[i] = aux.weigthPerWagon[i];
		}
		return *this;
	}

	friend ostream& operator<<(ostream&, FreightTrainRoute);
	friend istream& operator>>(istream&, FreightTrainRoute&);
};

//8. Supraincarcati operatorii de citire si afisare pentru clasa derivata
//cel de afisarea arata in plus urmatoarele linii la consola
//Nb of wagons: nbOfWagons
//Weigth per wagon: weigth1 weigth2 etc.
//se va afisa doar partea intreaga a greutatilor (fara zecimale)
//cel de citire va citi in continuare numarul de vagoane de pe o linie noua
//si greutatile separate prin spatii
/*int nbOfWagons;
float* weigthPerWagon;*/

ostream& operator<<(ostream& o, FreightTrainRoute f)		//op afisare(scriere)
{
	o << (TrainRoute&)f;		// apel construc de copiere si operat= clasa baza
	o << "Nb of wagons: ";
	o << f.nbOfWagons << endl;
	o << "Weigth per wagon: ";
	if (f.weigthPerWagon != nullptr)
	{
		for (int i = 0; i < f.nbOfWagons; i++)
		{
			//o << fixed << setprecision(0) << f.weigthPerWagon[i] << " ";		//?????? rotunjeste la n zecimala
			o << floor(f.weigthPerWagon[i]) << " ";						// rotunjeste la urm nr mai mic decat intregul (30.8 => 30)
		}																// nu merge pt <0 (rezultat fals pozitiv), dar nu pot sa am -10 kg

	}
	return o;
}

istream& operator>>(istream& i, FreightTrainRoute& f)		//op citire
{
	i >> (TrainRoute&)f;
	i >> f.nbOfWagons;

	if (f.weigthPerWagon != nullptr)
	{
		delete[] f.weigthPerWagon;
	}
	//validare biti bad si fail stream de intrare
	if (i.good() && f.nbOfWagons > 0)
	{
		f.weigthPerWagon = new float[f.nbOfWagons];
		for (int a = 0; a < f.nbOfWagons; a++)
		{
			i >> f.weigthPerWagon[a];
			cout << " ";
		}
	}
	else
	{
		f.nbOfWagons = 0;
		f.weigthPerWagon = nullptr;
	}
	return i;
}

//3. Modificati operatorul de scriere(afisare) la consola pentru a afisa informatiile despre ruta
//se pot folosi functii friend sau getteri
//afisarea va fi de forma:
//Departure: departure		(string)
//Destination: destination  (string)
//Train code: trainCode		(char*)

ostream& operator<<(ostream& o, TrainRoute t)
{
	o << "Departure: ";
	o << t.departure << endl;
	o << "Destination: ";
	o << t.destination << endl;

	o << "Train code: ";
	if (t.trainCode != nullptr)
	{
		o << t.trainCode;
	}
	else o << "Nu exista cod alocat de tren";
	o << endl;

	return o;
}

//Modificati operatorul de citire de la consola pentru a citi informatii despre ruta
//se vor citi in ordine urmatoarele informatii (fiecare pe o linie noua)
//Departure		(string)
//Destination   (string)
//Train code	(char*)
//se pot folosi setteri sau functii friend
//operatorul trebuie sa poata citi siruri de caractere ce contin spatii
istream& operator>>(istream& i, TrainRoute& t)
{
	cout << "Departure: ";
	getline(i, t.departure);
	cout << endl;
	cout << "Destination: ";
	getline(i, t.destination);
	string buf;
	cout << endl;
	cout << "Train code: ";		// !!! Train Code (nu trainCode)
	getline(i, buf);

	if (t.trainCode != nullptr)
	{
		delete[] t.trainCode;
	}
	t.trainCode = new char[buf.length() + 1];
	strcpy_s(t.trainCode, buf.length() + 1, buf.c_str());

	return i;
}

//ATENTIE!!!
//* Sunt punctate doar solutiile originale si individuale
//* Orice incercare de frauda va duce la pierderea intregului punctaj de la seminar
//* Signatura functiilor se poate modifica doar pentru a realiza supradefinirea
//* Utilizarea valorilor din teste pentru a obtine rezultate fals pozitive este considerata frauda

//1. Modificati constructorul cu parametri din clasa TrainRoute pentru a initializa
//statia de plecare, statia de sosire si codul trenului

//2. Respectati "regula celor 3" in cadrul clasei TrainRoute

//3. Modificati operatorul de scriere la consola pentru a afisa informatiile despre ruta
//se pot folosi functii friend sau getteri
//afisarea va fi de forma:
//Departure: departure
//Destination: destination
//Train code: trainCode

//Modificati operatorul de citire de la consola pentru a citi informatii despre ruta
//se vor citi in ordine urmatoarele informatii (fiecare pe o linie noua)
//Departure
//Destination
//Train code
//se pot folosi setteri sau functii friend
//operatorul trebuie sa poata citi siruri de caractere ce contin spatii

//4. Modificati constructorul implicit al clasei FreightTrainRoute
//acesta va initializa numarul de vagoane cu 0 si vectorul de greutati cu nullptr
//statia de plecare si destinatia vor fi initializate cu un sir vid
//codul trenului va fi "Necunoscut"

//5. Modificati constructorului cu parametri al clasei FreightTrainRoute
//astfel incat sa initializeze corect statia de plecare, destinatia si codul trenului
//numarul de vagoane si vectorul de greutati vor ramane 0, respectiv nullptr
//clasa TrainCode nu se poate modifica pentru a contine constructor implicit

//6. Modificati metoda setWeigth astfel incat sa se poata modifica
//vectorul de greutati si numarul de vagoane

//7. Aplicati "regula celor 3" si in clasa derivata

//8. Supraincarcati operatorii de citire si afisare pentru clasa derivata
//cel de afisarea arata in plus urmatoarele linii la consola
//Nb of wagons: nbOfWagons
//Weigth per wagon: weigth1 weigth2 etc.
//se va afisa doar partea intreaga a greutatilor (fara zecimale)
//cel de citire va citi in continuare numarul de vagoane de pe o linie noua
//si greutatile separate prin spatii

//9. Supradefiniti metoda totalWeight in clasa FreightTrainRoute
//astfel incat sa returneze greutatea totala a trenului ca intreg
//prin trunchiere (se ignora zecimalele rezultatului final)

//10. Evitati memory leaks generate odata cu virtualizarea

int main()
{
	TrainRoute a("buc", "camp", "RE1123");
	/*TrainRoute b;
	b = a;*/
	FreightTrainRoute b("buc", "clj", "TGV999");
	float greutati[] = { 15.23, 31.88 };
	b.setWeigth(2, greutati);			// seteaza greutatile trenului(in parametrul float* weightPerWag) din multimea greutati[]
	int x = b.totalWeight();			// calculeaza masa totala(in INT) si returneaza

	/*FreightTrainRoute c = b;
	FreightTrainRoute d;
	d = b;*/

}