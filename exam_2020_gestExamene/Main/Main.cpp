#include <iostream>
#include<string>

using namespace std;

class Examen 
{
	const int idExamen;	 //un atribut de tip constant(Const) nu modifica valoarea pe parcursul rularii programului
	static int contor;	//un atribut de tip static apartine intregii clasei(adica va avea aceeasi valoare pentru orice obiect creat)
protected:
	char* materie;
	string profesor;
	int nota;
	int data[3];		//vect alocat static pt ca ii cunoastem deja dimens (3: zi luna an)
	int nrSubiect;
	float* punctajSubiecte;

public:
	//constructor default/implicit/fara parametrii
	//sunt utilizati la crearea obiectelor
	Examen() :idExamen(10001)
	{
		//pt char* si string se hardcodeaza(se da) un mesaj
		this->materie = new char[strlen("Necunoscut") + 1];				//+1 vine de la terminatorul '\0'
		strcpy_s(this->materie, strlen("Necunoscut") + 1, "Necunoscut");

		this->profesor = "Toma Adrian";
		this->nota = 0;
		this->data[0] = 1;
		this->data[1] = 1;
		this->data[2] = 2010;
		this->nrSubiect = 0;
		//pentru atributele alocate dinamic(in afara de char*) dam valoarea nullptr;
		this->punctajSubiecte = nullptr;
	}

	Examen(int id, const char* materie, string profesor, int nota, int data[3], int nrSub, float* punctajSub)
		:idExamen(id > 0 ? id:0)
	{
		this->materie = new char[strlen(materie) + 1];
		strcpy_s(this->materie, strlen(materie) + 1, materie);

		this->profesor = profesor;
		this->nota = nota;
		for (int i = 0; i < 3; i++) {
			this->data[i] = data[i];
		}
		
		this->nrSubiect = nrSub;
		
		if (this->nrSubiect != 0) {
			this->punctajSubiecte = new float[this->nrSubiect];		//atatea pct cate subiecte (new float de this.)
			for (int i = 0; i < this->nrSubiect; ) {
				this->punctajSubiecte[i] = punctajSub[i];
				i++;
			}
		}
		else
			this->punctajSubiecte = nullptr;
		
	}

	//getteri --- functii accesor care permit citirea unei valori dintr-un atribut
	//cum se construieste un getter:
	//sablon getter
	/*
		tipVariabila getNumeVariabila()
		{
			return this->variabila;
		}
	*/
	int getNota()
	{
		return this->nota;
	}

	char* getMaterie()
	{
		return this->materie;
	}

	int* getData()
	{
		return this->data;
	}
	//constructor de copiere --- se apeleaza atunci cand dorim/vrem sa cream 
	//un obiect nou pe baza altuia deja existent (clone() din Java)
	//constructorul de copiere seamana cu constructorul cu toti parametrii
	Examen(const Examen& e) 
		:idExamen(e.idExamen)
	{
		this->materie = new char[strlen(e.materie) + 1];
		strcpy_s(this->materie, strlen(e.materie) + 1, e.materie);

		this->profesor = e.profesor;
		this->nota = e.nota;
		for (int i = 0; i < 3; i++) {
			this->data[i] = e.data[i];
		}

		this->nrSubiect = e.nrSubiect;

		if (this->nrSubiect != 0) {
			this->punctajSubiecte = new float[this->nrSubiect];		//atatea pct cate subiecte (new float de this.)
			for (int i = 0; i < this->nrSubiect; ) {
				this->punctajSubiecte[i] = e.punctajSubiecte[i];
				i++;
			}
		}
		else
			this->punctajSubiecte = nullptr;
	}
};

int Examen::contor = 1;




void main()
{
	Examen e;
	//char nume[] = "Economie";		il fac 'const' in constructor
	int data[3] = { 20, 1, 2016 };
	Examen e1(77, "Economie", "Moraru", 9, data, 0, nullptr);

	//cout << e1.materie << endl;		//inaccesibil (tip private)		=>> Getteri si Setteri
	cout << e1.getMaterie() << endl;

	for (int i = 0; i < 3; i++)
	{
		cout << e1.getData()[i] << "/";

	}
	cout << endl;

	Examen e2 = e1;
	//Examen e2(e1); -- ambele forme sunt corecte
	cout << e2.getMaterie() << endl;
}