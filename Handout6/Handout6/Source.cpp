#include <iostream>
#include <string>
#include <iomanip>
#include<fstream>
using namespace std;

class TrainRoute
{
private:
	string departure;
	string destination;
	int nbOfStops;
	//distances between stops
	//it has nbOfStops - 1 elements
	int* distances;
	char* trainCode;

public:
	//1. Modificati constructorul cu parametri pentru a initializa
//statia de plecare si statia de sosire
//numarul de opriri va fi initializat cu 0, iar cei doi vectori
//(vectorul de distante si codul trenului) cu null
	TrainRoute(string departure, string destination)
	{
		this->destination = destination;
		this->departure = departure;
		nbOfStops = 0;
		distances = nullptr;
		trainCode = nullptr;
	}

	TrainRoute(const TrainRoute& aux)

	{
		departure = aux.departure;
		destination = aux.destination;
		if (aux.distances != nullptr && aux.nbOfStops > 1) {
			nbOfStops = aux.nbOfStops;
			distances = new int[aux.nbOfStops - 1];
			for (int i = 0; i < nbOfStops - 1; i++)
			{
				distances[i] = aux.distances[i];
			}
		}
		else {
			distances = nullptr;
			nbOfStops = 0;
		}
		if (aux.trainCode != nullptr) {
			trainCode = new char[strlen(aux.trainCode) + 1];
			strcpy_s(trainCode, strlen(aux.trainCode) + 1, aux.trainCode);
		}
		else trainCode = nullptr;
	}

	TrainRoute operator=(const TrainRoute& aux)
	{
		if (distances != nullptr) {
			delete[] distances;
			distances = nullptr;
		}
		if (trainCode != nullptr) {
			delete[] trainCode;
			trainCode = nullptr;
		}

		departure = aux.departure;
		destination = aux.destination;
		if (aux.distances != nullptr && aux.nbOfStops > 1) {
			nbOfStops = aux.nbOfStops;
			distances= new int[nbOfStops - 1];
			for (int i = 0; i < nbOfStops - 1; i++)
			{
				distances[i] = aux.distances[i];
			}
		}
		else this->distances = nullptr;

		if (aux.trainCode != nullptr) {
			trainCode = new char[strlen(aux.trainCode) + 1];
			strcpy_s(trainCode, strlen(aux.trainCode) + 1, aux.trainCode);
		}
		else this->trainCode = nullptr;

		return *this;
	}


	~TrainRoute()
	{
		if (distances != nullptr) {
			delete[] distances;
		}
		if (trainCode != nullptr) {
			delete[] trainCode;
		}		
	}
	//2. Modificati metoda setTrip astfel incat vectorul existent de distante
	//sa fie inlocuit de cel primit drept parametru
	//nu uitati faptul ca vectorul are cu un element mai putin decat numarul de statii
	void setTrip(int* distances, int nbOfStops)
	{
		int i = 0;
		int opriri = nbOfStops - 1;
		
		if(distances != nullptr && nbOfStops > 1)
		{
			this->distances = new int[opriri];
			for (int i = 0; i < opriri; i++) {
				this->distances[i] = distances[i];
			}
			this->nbOfStops = nbOfStops;
		}
		
	}

	//3. Modificati metoda setTrainCode pentru a inlocui codul existent
//cu cel primit drept parametru
	void setTrainCode(const char* trainCode)
	{
		if (trainCode != nullptr)
		{
			this->trainCode = new char[strlen(trainCode) + 1];
			strcpy_s(this->trainCode, strlen(trainCode) + 1, trainCode);
		}
	}


	//5. Modificati supraincarcarea operatorului <
//acesta va returna true daca distanta totala a rutei reprezentata de primul operand
//este mai mica decat distanta totala a rutei reprezentate de al doilea operand
	bool operator<(TrainRoute t)
	{
		int x = 0;
		int y = 0;
		for (int i = 0; i < nbOfStops; i++)
		{
			x = x + distances[i];
		}
		for (int i = 0; i < t.nbOfStops; i++) 
		{
			y = y + t.distances[i];
		}
		if (x < y) {
			return true;
		}
		else return false;
	}

	// 6. Modificati operatorul += pentru a adauga un element in vectorul de distante
//numarul de statii va fi de asemenea incrementat
	//string departure;
	//string destination;
	//int nbOfStops;
	
	//int* distances;
	//char* trainCode;
	void operator+=(int distance)
	{
		int* source = new int[nbOfStops];
		for (int i = 0; i <= nbOfStops - 1; i++)
		{
			source[i] = distances[i];
		}
		source[nbOfStops - 1] = distance;
		nbOfStops++;

		distances = new int[nbOfStops - 1];
		for (int i = 0; i < nbOfStops - 1; i++) 
		{
			distances[i] = source[i];
		}
	}

	string getDeparture()
	{
		return departure;
	}
	string getDestination()
	{
		return destination;
	}


	void serialize(string fileName)
	{

	}

	void deserialize(string fileName)
	{

	}

	friend ostream& operator<<(ostream&, TrainRoute );
	friend istream& operator>>(istream&, TrainRoute&);
};
//7. Modificati operatorul de scriere la consola pentru a afisa informatiile despre ruta
//se pot folosi functii friend sau getteri
//afisarea va fi de forma:
//Departure: departure		 (string)
//Destination: destination	 (string)
//Train code: trainCode		 (char*)
//Number of stops: nbOfStops (int)
//Distances between stops: distance1 distance2 distance3 etc  (int*)
ostream& operator<<(ostream& out, TrainRoute r)
{
	out << "Departure: ";
	out << r.departure << endl;
	out << "Destination: ";
	out << r.destination << endl;

	out << "Train code: ";
	if (r.trainCode != nullptr) {
		out << r.trainCode;
	}
	else out << "N/A";
	out << endl;

	out << "Number of stops: ";
	out << r.nbOfStops << endl;

	out << "Distances between stops: ";
	if (r.distances != nullptr) {
		for (int i = 0; i < r.nbOfStops - 1; i++)
		{
			out << r.distances[i] << " ";
		}
	}
	return out;
}

//8. Modificati operatorul de citire de la consola pentru a citi informatii despre ruta
//se vor citi in ordine urmatoarele informatii (fiecare pe o linie noua)
//Departure
//Destination
//Train code
//Number of stops
//distance 1
//distance 2
//distance 3
//etc
//se pot folosi setteri sau functii friend
//operatorul trebuie sa poata citi siruri de caractere ce contin spatii
istream& operator>>(istream& in, TrainRoute& r)
{
	cout << "Departure = ";
	getline(in, r.departure);
	cout << "Destination = ";
	getline(in, r.destination);
	string buf;
	cout << "train code = ";
	//in >> ws;
	getline(in, buf);

	if (r.trainCode != nullptr)
	{
		delete[] r.trainCode;
	}
	r.trainCode = new char[buf.length() + 1];
	strcpy_s(r.trainCode, buf.length() + 1, buf.c_str());

	cout << "numar opriri = ";
	in >> r.nbOfStops;
	r.distances = new int[r.nbOfStops - 1];

	for (int i = 0; i < r.nbOfStops-1; i++) {
		in >> r.distances[i];
	}
	return in;
}

//ATENTIE!!!
//* Sunt punctate doar solutiile originale si individuale
//* Orice incercare de frauda va duce la pierderea intregului punctaj de la seminar
//* Signatura functiilor nu se poate modifica, doar continului lor
//* Utilizarea valorilor din teste pentru a obtine rezultate fals pozitive este considerata frauda

//1. Modificati constructorul cu parametri pentru a initializa
//statia de plecare si statia de sosire
//numarul de opriri va fi initializat cu 0, iar cei doi vectori
//(vectorul de distante si codul trenului) cu null

//2. Modificati metoda setTrip astfel incat vectorul existent de distante
//sa fie inlocuit de cel primit drept parametru
//nu uitati faptul ca vectorul are cu un element mai putin decat numarul de statii

//3. Modificati metoda setTrainCode pentru a inlocui codul existent
//cu cel primit drept parametru

//4. Respectati "regula celor 3" in cadrul clasei de mai sus

//5. Modificati supraincarcarea operatorului <
//acesta va returna true daca distanta totala a rutei reprezentata de primul operand
//este mai mica decat distanta totala a rutei reprezentate de al doilea operand

//6. Modificati operatorul += pentru a adauga un element in vectorul de distante
//numarul de statii va fi de asemenea incrementat

//7. Modificati operatorul de scriere la consola pentru a afisa informatiile despre ruta
//se pot folosi functii friend sau getteri
//afisarea va fi de forma:
//Departure: departure
//Destination: destination
//Train code: trainCode
//Number of stops: nbOfStops
//Distances between stops: distance1 distance2 distance3 etc

//8. Modificati operatorul de citire de la consola pentru a citi informatii despre ruta
//se vor citi in ordine urmatoarele informatii (fiecare pe o linie noua)
//Departure
//Destination
//Train code
//Number of stops
//distance 1
//distance 2
//distance 3
//etc
//se pot folosi setteri sau functii friend
//operatorul trebuie sa poata citi siruri de caractere ce contin spatii

//9. Supraincarcati operatorii de scriere si citire din fisiere text
//operatorii functioneaza pe fisiere text deschise deja

//10. Modificati metodele serialize si deserialize pentru a scrie
//si a citi obiectul curent de clasa TrainRoute intr-un/dintr-un fisier binar
//se vor serializa toate campurile (ordinea nu conteaza)
//numele fisierului este primit drept parametru
//metodele deschid si inchid fisierele specificate

int main()
{
	
}