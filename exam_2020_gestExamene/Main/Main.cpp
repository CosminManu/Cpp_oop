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
	Examen() :idExamen(contor++)
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
		//pentru atributele alocate dinamic(in afara de char* unde dam mesaj) dam valoarea nullptr;
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


	const int getIdExamen()
	{
		return this->idExamen;
	}

	string getProfesor()
	{
		return this->profesor;
	}

	int getNota()
	{
		return this->nota;
	}

	char* getMaterie()
	{
		return this->materie;
	}

	int* getData()		//int* pt ca returnam adresa intreg vector static
	{
		return this->data;
	}

	int getNrSubiecte()
	{
		return this->nrSubiect;
	}

	float* getPunctajSubiecte()
	{
		return this->punctajSubiecte;
	}

//char* materie;
//int nota;
//int data[3];		
//int nrSubiect;
//float* punctajSubiecte;

	void setProfesor(string _profesor)
	{
		this->profesor = _profesor;
	}

	void setMaterie(const char* _materie) 
	{
		this->materie = new char[strlen(_materie) + 1];
		strcpy_s(this->materie, strlen(_materie) + 1, _materie);
	}

	void setData(int* _data)
	{
		for (int i = 0; i < 3; i++) {
			this->data[i] = _data[i];
		}
	}

	void setPunctajSubiecte(int _nrSub, float* _punctajSub)
	{
		this->nrSubiect = _nrSub;
		if (this->nrSubiect != 0) {
			this->punctajSubiecte = new float[this->nrSubiect];		//atatea pct cate subiecte (new float de this.)
			for (int i = 0; i < this->nrSubiect; ) {
				this->punctajSubiecte[i] = _punctajSub[i];
				i++;
			}
		}
		else
			this->punctajSubiecte = nullptr;
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

	//destruc dezaloca mem din zona heap
	//de cate ori se apeleaza construc => apeleaza destruc
	~Examen()
	{
		if (this->materie != nullptr){
			delete[] this->materie;
		}
		
		if (this->punctajSubiecte != nullptr) {
			delete[] this->punctajSubiecte;
		}
		
		cout << "apel destructor" << endl;
	}

	//op =	destruc + cons_copi + return *this;
	//rolul de a copia elem 
	//dintr un ob deja existent in altul acelasi tip
	Examen& operator=(const Examen& s)	//primes param de tip referinta la ob const de tip Examen
	{
		//evitarea auto-asignarii(nu putem sa facem un obiect egal cu el insusi --- ex:e1=e1)
		if (this != &s)
		{
			if (this->materie != nullptr) {
				delete[] this->materie;
			}

			if (this->punctajSubiecte != nullptr) {
				delete[] this->punctajSubiecte;
			}

			this->materie = new char[strlen(s.materie) + 1];
			strcpy_s(this->materie, strlen(s.materie) + 1, s.materie);
			this->profesor = s.profesor;
			this->nota = s.nota;
			for (int i = 0; i < 3; i++) {
				this->data[i] = s.data[i];
			}
			this->nrSubiect = s.nrSubiect;
			if (this->nrSubiect != 0) {
				this->punctajSubiecte = new float[this->nrSubiect];		//atatea pct cate subiecte (new float de this.)
				for (int i = 0; i < this->nrSubiect; ) {
					this->punctajSubiecte[i] = s.punctajSubiecte[i];
					i++;
				}
			}
			else
				this->punctajSubiecte = nullptr;
			
		}
		return *this;		//fara prima referinta& se apel construc copiere
	}
};

int Examen::contor = 1;


//char* materie;
//string profesor;
//int nota;
//int data[3];		//vect alocat static pt ca ii cunoastem deja dimens (3: zi luna an)
//int nrSubiect;
//float* punctajSubiecte;

int main()
{
	Examen e;
	//char nume[] = "Economie";		il fac 'const' in constructor
	int data[3] = { 20, 1, 2016 };
	float pct[] = { 8.8, 9.2, 7.9, 10 };
	Examen e1(77, "Economie", "Moraru", 9, data, 4, pct);

	//cout << e.getData() << endl;//asa afisam adresa vectorului
	for (int i = 0; i < 3; i++) {
		cout << e1.getData()[i] << "/";

	}
	cout << endl;

	//cout << e1.materie << endl;		//inaccesibil (tip private)		=>> Getteri si Setteri
	cout << e1.getMaterie() << endl;
	for (int i = 0; i < e1.getNrSubiecte();) {
		cout << e1.getPunctajSubiecte()[i] << endl;
		i++;
	}

	e1.setMaterie("Mate");
	e1.setMaterie("Biologie");

	int data1[3] = { 07, 07, 2021 };
	e1.setData(data1);
	for (int i = 0; i < 3; i++) {
		cout << e1.getData()[i] << "/";
	}
	cout << endl;

	Examen e2 = e1;		//construc copiere
	//Examen e2(e1); -- ambele forme sunt corecte
	cout << e2.getMaterie() << endl;

	//INT* FLOAT* => parcurse cu for si INDEXATE de i ([i])
	float pct1[] = { 12.3, 23.6, 23.56, 84, 21};
	e2.setPunctajSubiecte(5, pct1);
	for (int i = 0; i < 5; ) {
		cout << e2.getPunctajSubiecte()[i] << endl;
		i++;
	}
	cout << endl;
	
	float pct2[] = {34.5, 345.6, 23.98, 10.23, 456.654 };
	e2.setPunctajSubiecte(5, pct2);
	for (int i = 0; i < 5; i++)
	{
		cout << e2.getPunctajSubiecte()[i] << endl;
	}

	Examen e3;
	e3 = e2;
	e1 = e1;
}
