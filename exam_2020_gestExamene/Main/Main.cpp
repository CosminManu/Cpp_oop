#include <iostream>
#include<string>
#include <fstream>

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
		if (_profesor.size() > 2) {
			this->profesor = _profesor;
		}
		else throw exception();
	}

	void setNota(int _nota)
	{
		if (_nota > 0 && _nota <= 10) {
			this->nota = _nota;
		}
		else
			this->nota = -1;
	}

	void setMaterie(const char* _materie) 
	{
		if (strlen(_materie) > 2) {
			this->materie = new char[strlen(_materie) + 1];
			strcpy_s(this->materie, strlen(_materie) + 1, _materie);
		}
		else {
			this->materie = new char[strlen("N/A") + 1];				//+1 vine de la terminatorul '\0'
			strcpy_s(this->materie, strlen("N/A") + 1, "N/A");
		}
	}

	void setData(int* _data)
	{
		if (_data[0] >= 1 && _data[0] <= 31 && _data[1] >= 1 && _data[1] <= 12 && _data[2] >= 2000 ) {
			for (int i = 0; i < 3; i++) {
				this->data[i] = _data[i];
			}
		}
	}

	void setPunctajSubiecte(int _nrSub, float* _punctajSub)
	{
		if (_nrSub > 0 && _punctajSub != nullptr)
		{
			this->nrSubiect = _nrSub;
			
			this->punctajSubiecte = new float[this->nrSubiect];		//atatea pct cate subiecte (new float de this.)
			for (int i = 0; i < this->nrSubiect; ) {
				this->punctajSubiecte[i] = _punctajSub[i];
				i++;
			}
		}
		else {
			this->nrSubiect = 0;
			this->punctajSubiecte = nullptr;
		}
			

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
	
	//======================================Tutoring vin=======================
	//op+ : ob + valoare (e4 + 10)
	Examen operator+(int valoare) {
		Examen copie = *this;
		if (copie.nota + valoare)
		{
			copie.nota += valoare;
		}
		return copie;
	}

	//op+ : ob + ob (e4 + e3)
	Examen operator+(Examen ex)
	{
		//adunarte 2 char*
		Examen copie = *this;
		string aux1, aux2;
		aux1 = ex.materie;
		aux2 = copie.materie;
		aux2 += " - " + aux1;

		if (copie.materie != nullptr) {
			delete[] copie.materie;
		}
		copie.materie = new char[strlen(ex.materie) + 1];
		strcpy_s(copie.materie, strlen(ex.materie) + 1, ex.materie);
	
		//adunare 2 string
		copie.profesor += " - "; 
		copie.profesor += ex.profesor;

		//adunare 2 note
		copie.nota += ex.nota;

		if (copie.punctajSubiecte != nullptr)
		{
			delete[] copie.punctajSubiecte;
		}
		copie.nrSubiect += ex.nrSubiect;
		copie.punctajSubiecte = new float[copie.nrSubiect];
		for (int i =0; i<this->nrSubiect; i++)
		{
			copie.punctajSubiecte[i] = this->punctajSubiecte[i];
		}
		for (int i = 0; i < ex.nrSubiect; i++)
		{
			copie.punctajSubiecte[i + this->nrSubiect] = this->punctajSubiecte[i];
		}
		for (int i = this->nrSubiect; i < copie.nrSubiect; i++)
		{
			copie.punctajSubiecte[i] = ex.punctajSubiecte[i - this->nrSubiect];
		}
	}

	friend ostream& operator<<(ostream& out, const Examen e)
	{
		out << "ID:" << e.idExamen << endl;
		out << "Materie:" << e.materie << endl;
		out << "Profesor:" << e.profesor << endl;
		out << "Nota:" << e.nota << endl;
		out << "Data:";
		for (int i = 0; i < 3; i++)
		{
			out << e.data[i] << "/";

		}
		out << endl;
		out << "Numar Subiecte:" << e.nrSubiect << endl;
		out << "Punctaj subiecte: ";
		for (int i = 0; i < e.nrSubiect; i++)
		{
			out << e.punctajSubiecte[i] << " | ";

		}
		out << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Examen& e)
	{
		if (e.materie != NULL)
		{
			delete[]e.materie;
		}
		if (e.punctajSubiecte != NULL)
		{
			delete[]e.punctajSubiecte;
		}
		//op>> pentru char*
		cout << "Materie:";
		in >> ws;
		char aux[250];
		in.getline(aux, 249);
		e.materie = new char[strlen(aux) + 1];
		strcpy(e.materie, aux);
		//op>> pentru string
		cout << "Profesor:";
		getline(in, e.profesor);
		//op>> pentru int
		cout << "Nota:";
		in >> e.nota;
		//op>> pentru int static sau int*
		cout << "Data(zi/ luna/ an):";
		for (int i = 0; i < 3; i++)
		{
			in >> e.data[i];
		}
		//op>> pentru int
		cout << "Numar Subiecte:";
		in >> e.nrSubiect;
		//op>> pentru int static sau int*
		cout << "Punctaj Subiecte:";
		e.punctajSubiecte = new float[e.nrSubiect];
		for (int i = 0; i < e.nrSubiect; i++)
		{
			in >> e.punctajSubiecte[i];
		}
		return in;
	}

	friend ofstream& operator<<(ofstream& out, const Examen e)
	{
		out << e.idExamen << endl;
		out << e.materie << endl;
		out << e.profesor << endl;
		out << e.nota << endl;
		out << "Data:";
		for (int i = 0; i < 3; i++)
		{
			out << e.data[i] << "/";

		}
		out << endl;
		out << "Numar Subiecte:" << e.nrSubiect << endl;
		out << "Punctaj subiecte: ";
		for (int i = 0; i < e.nrSubiect; i++)
		{
			out << e.punctajSubiecte[i] << " | ";

		}
		out << endl;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Examen& e)
	{
		if (e.materie != NULL)
		{
			delete[]e.materie;
		}
		if (e.punctajSubiecte != NULL)
		{
			delete[]e.punctajSubiecte;
		}
		//op>> pentru char*
		cout << "Materie:";
		in >> ws;
		char aux[250];
		in.getline(aux, 249);
		e.materie = new char[strlen(aux) + 1];
		strcpy(e.materie, aux);
		//op>> pentru string
		cout << "Profesor:";
		getline(in, e.profesor);
		//op>> pentru int
		cout << "Nota:";
		in >> e.nota;
		//op>> pentru int static sau int*
		cout << "Data(zi/ luna/ an):";
		for (int i = 0; i < 3; i++)
		{
			in >> e.data[i];
		}
		//op>> pentru int
		cout << "Numar Subiecte:";
		in >> e.nrSubiect;
		//op>> pentru int static sau int*
		cout << "Punctaj Subiecte:";
		e.punctajSubiecte = new float[e.nrSubiect];
		for (int i = 0; i < e.nrSubiect; i++)
		{
			in >> e.punctajSubiecte[i];
		}
		return in;
	}


	//fis binare
	//fara const sau static
	//serializare - transf un ob in octeti
	void serializare(string numefisier) 
	{
		ofstream f(numefisier, ios::out | ios::binary);

		int dimensMaterie = strlen(this->materie);
		f.write( (char*) dimensMaterie, sizeof(dimensMaterie));
		f.write( this->materie, dimensMaterie + 1);



	}

	//deserializ - invers serial
	void deserializare(string numefisier) 
	{

	}
};

int Examen::contor = 1;


//char* materie;
//string profesor;
//int nota;
//int data[3];		//vect alocat static pt ca ii cunoastem deja dimens (3: zi luna an)
//int nrSubiect;
//float* punctajSubiecte;


//Mostenire/derivare - relatie de is a - trecere de la gen => particul
class ExamenLicenta :private Examen
{
	string temaLicenta;
	int comisie;
public:
	ExamenLicenta()
		:Examen()
	{
		this->temaLicenta = "NA";
		this->comisie = 0;
	}





};

// functii Template = sablon
template<typename tipData>
tipData suma(tipData a, tipData b)
{
	return a + b;
}

template<typename clasa>
void afisare(clasa a)
{
	cout << a << endl;
}

//clase template
template<typename clasaUtiliz>
class Sablon
{
	//Neterminat
};

int main()
{
	Examen e;
	//char nume[] = "Economie";		il fac 'const' in constructor
	int data[3] = { 20, 1, 2016 };
	float pct[] = { 8.8, 9.2, -1, 10 };
	Examen e1(77, "Economie", "Moraru", 9, data, 4, pct);

	//cout << e.getData() << endl;//asa afisam adresa vectorului
	for (int i = 0; i < 3; i++) {
		cout << e1.getData()[i] << "/";

	}
	cout << endl;

	//cout << e1.materie << endl;		//inaccesibil (tip private)		=>> Getteri si Setteri
	cout << e1.getMaterie() << endl;
	cout << "Punctaj: ";
	for (int i = 0; i < e1.getNrSubiecte();) {
		cout << e1.getPunctajSubiecte()[i] << " | ";
		i++;
	}
	cout << endl;

	e1.setMaterie("SO");
	cout << "Materia: " << e1.getMaterie() << endl;
	e1.setMaterie("Biologie");
	cout << "Materia: " << e1.getMaterie() << endl;
	string nume;

	//do {
	//	cout << "Introduce ti numele profesor: ";
	//	cin >> nume;
	//	try {
	//		e1.setProfesor(nume);
	//	}
	//	catch (exception ex)
	//	{
	//		cout << "Nume prof incorect" << endl << endl;
	//	}
	//} while (nume.size() < 3);		//introduci pana cand numele > 2
	
	
	int data1[3] = { 07, 07, 2021 };
	e1.setData(data1);
	for (int i = 0; i < 3; i++) {
		cout << e1.getData()[i] << "/";
	}
	cout << endl;

	Examen e2 = e1;		//construc copiere
	//Examen e2(e1); -- ambele forme sunt corecte
	cout << e2.getMaterie() << endl;

	e2.setNota(10);
	cout <<"Nota (-1 nu e nota corecta): "<< e2.getNota() << endl << endl;

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
	cout << "Punctaj: ";
	for (int i = 0; i < 5; i++)
	{
		cout << e2.getPunctajSubiecte()[i] << " | ";
	}
	cout << endl;

	Examen e3;
	e3 = e2;
	e1 = e1;


	//tutoring vineri
	Examen e5 = e3 + 10;
	Examen e7 = e5 + e3;

	ofstream f;
	f.open("tutoring_vin.txt", ios::out);
	f << e1;

	ifstream fis;
	fis.open("tutoring.txt", ios::in);


	ExamenLicenta el1;
	ExamenLicenta el2;


	cout << "-------------------------------Functii Template--------------" << endl;
	string x = "Casa";
	string y = "Masa";
	cout << suma(x, y) << endl;
	afisare(e3);

}
