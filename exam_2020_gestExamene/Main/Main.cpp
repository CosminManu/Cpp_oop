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

	//validare pe nota
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

	//METODE  -- fct  interiorul clasei care primesc *this
	//suma
	float totalPunctajeSubiect()
	{
		float total = 0;
		if (this->nrSubiect > 0 && this->punctajSubiecte != nullptr) {
			for (int i = 0; i < this->nrSubiect; i++) {
				total += this->punctajSubiecte[i];
			}
		}
		return total;
	}
	
	float mediePunctaje()
	{
		float total = totalPunctajeSubiect();
		float medie = total / this->nrSubiect;
	}

	float minPunctaje()
	{
		float min = this->punctajSubiecte[0];
		for (int i = 0; i < this->nrSubiect; i++) {
			if (min > this->punctajSubiecte[i]) {
				min = this->punctajSubiecte[i];
			}
		}
		return min;
	}

	float maxPunctaje()
	{
		float max = this->punctajSubiecte[0];
		for (int i = 0; i < this->nrSubiect; i++)
		{
			if (max < this->punctajSubiecte[i])
			{
				max = this->punctajSubiecte[i];
			}
		}
		return max;
	}

	bool areRestanta()
	{
		return this->nota < 5;
	}

	bool examenulEsteRestanta()
	{
		return data[1] == 7;
	}

	//adaug punctaj in vect de float*
	//fac copie vect vechi, sterg vect vechi, maresc dim this +1, aloc mem
	// copiez in vect nou si adaug pe ultima poz
	void adaugaSubiect(float punctaj)
	{
		Examen copie = *this;
		delete[] this->punctajSubiecte;
		this->nrSubiect++;
		this->punctajSubiecte = new float[this->nrSubiect];
		for (int i = 0; i < copie.nrSubiect; i++) 
		{
			this->punctajSubiecte[i] = copie.punctajSubiecte[i];
		}
		this->punctajSubiecte[this->nrSubiect - 1] = punctaj;
	}

	//fac copie vect vechi, parcurg ca sa vad de cate ori (int n) apare param punctaj,
	//sterg vect vechi this, aloc mem in this de (dim initiala = dim initiala - n), parcurg copia si compar 
	// cu param, daca e != pun in this si cresc pozitie
	void eliminaSubiect(float punctaj)
	{
		Examen copie = *this;
		int nr = 0;//vom stoca aici de cate ori se gaseste numarul cautat in vector
		for (int i = 0; i < this->nrSubiect; i++)
		{
			if (punctaj == this->punctajSubiecte[i])
			{
				nr++;
			}
		}
		delete[]this->punctajSubiecte;
		this->nrSubiect = this->nrSubiect - nr;
		this->punctajSubiecte = new float[this->nrSubiect];
		int pozitie = 0;
		for (int i = 0; i < copie.nrSubiect; i++)
		{
			if (punctaj != copie.punctajSubiecte[i])
			{
				this->punctajSubiecte[pozitie] = copie.punctajSubiecte[i];
				pozitie++;
			}
		}
	}

	//OPERATORI >> << () cast []-indexare ++ preincreme += postincremen
	
	
	//friend --- ofera accesul la atributele din zona privata a unei clase 
	// fara sa aiba pointerul this;
	//friend se foloseste neaparat(ca nu se poate fara) atunci cand 
	// avem nevoie de un operator ce implica(are nevoie) de 2 termeni, unul in stanga altul in dreapta
	//iar cel din stanga nu este de tipul clasei --- ex(cout<<e1, cin>>e2;  e1= 44+e2;)

	friend ostream& operator<<(ostream&, const Examen);		//op <<	afisare OSTREAM - implemen afara clasei
	friend istream& operator>>(istream&, Examen&);			//op >>	citire ISTREAM - implemen afara clasei

	//[] op indexare
	float operator[] (int pozitie)		//float& pt a putea modif de la o adresa
	{
		if (pozitie > 0 && pozitie < this->nrSubiect) {
			return this->punctajSubiecte[pozitie];
		}
		else throw exception();
	}

	//() op functie
	int operator()(int marire) {
		if (this->nota < 10) {
			return this->nota + marire;
		}
		else return -1;
	}

	//cast implicit		--apel cast implicit/explicit
	/*operator string()
	{
		return this->profesor;
	}*/
	//cast explicit		-- apel se fol cast exlicit la tipul folosit (string)e2
	explicit operator string()
	{
		return this->profesor;
	}

	//operatori relationali -- >, <, >=, ==, !
	//cum func op si ce sens ii pot da in clasa mea
	bool operator<(int nr)
	{
		return this->nrSubiect < nr;
	}
	bool operator>(Examen e)
	{
		return this->nota > e.nota;
	}
	bool operator==(Examen e)
	{
		return this->profesor == e.profesor;
	}
	bool operator!()
	{
		bool restanta = 0;
		if (this->nota > 4)
		{
			restanta = 0;
			this->nota = 2;
		}
		else
		{
			restanta = 1;
			this->nota = 7;
		}
		return restanta;
	}
	bool operator~()
	{
		return this->nota > 4;
	}

	//operator += post incrementat(cu parametru)--- a=b++;
	// 1)a=b; atribuire 2)b++ adunare
	Examen operator ++(int i)
	{
		Examen copie = *this;
		if (this->nota <= 9)
		{
			this->nota++;
		}
		return copie;
	}

	//operator ++ pre incrementat --- a= ++b; 
	//1) b++; adunare 2)a = b atribuire
	Examen& operator ++()
	{
		if (this->nota <= 9)
		{
			this->nota++;
		}
		return *this;
	}

	//operator +=
	Examen& operator +=(float punctaj)
	{
		Examen copie = *this;
		delete[]this->punctajSubiecte;
		this->nrSubiect++;
		this->punctajSubiecte = new float[this->nrSubiect];
		for (int i = 0; i < copie.nrSubiect; i++)
		{
			this->punctajSubiecte[i] = copie.punctajSubiecte[i];
		}
		this->punctajSubiecte[this->nrSubiect - 1] = punctaj;
		return *this;
	}

	//operator -=
	Examen& operator -=(float punctaj)
	{
		Examen copie = *this;
		int nr = 0;//vom stoca aici de cate ori se gaseste numarul cautat in vector
		for (int i = 0; i < this->nrSubiect; i++)
		{
			if (punctaj == this->punctajSubiecte[i])
			{
				nr++;
			}
		}
		delete[]this->punctajSubiecte;
		this->nrSubiect = this->nrSubiect - nr;
		this->punctajSubiecte = new float[this->nrSubiect];
		int pozitie = 0;
		for (int i = 0; i < copie.nrSubiect; i++)
		{
			if (punctaj != copie.punctajSubiecte[i])
			{
				this->punctajSubiecte[pozitie] = copie.punctajSubiecte[i];
				pozitie++;
			}
		}
		return *this;
	}

	static float medieNoteExamene(int nrEx, Examen* vect)
	{
		float total = 0;
		for (int i = 0; i < nrEx; i++)
		{
			total += vect[i].getNota();
		}
		return total / nrEx;
	}

	//======================================Tutoring vin==============================================
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
		return copie;
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
		strcpy_s(e.materie, strlen(aux) + 1, aux);
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

ostream& operator<<(ostream& out, const Examen e)
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

//la citire intai dezalocam pointerii
//si apoi alocam iar
istream& operator>>(istream& in, Examen& e)
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
	in.getline(aux, 249);		//citire cu spatii
	e.materie = new char[strlen(aux) + 1];
	strcpy_s(e.materie, strlen(aux) + 1, aux);
	
	//op>> pentru string
	cout << "Profesor:";
	getline(in, e.profesor);	//citire cu spatii
	
	//op>> pentru int
	cout << "Nota:";
	in >> e.nota;
	
	//op>> pentru int static sau int*
	cout << "Data(zi/ luna/ an):";
	for (int i = 0; i < 3; i++)
	{
		in >> e.data[i];	//se da enter
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
	float pct[] = { 8.8, 9.2, 8.8, 10 };
	Examen e1(77, "Economie", "Moraru", 9, data, 4, pct);

	cout << "-------------------Getteri---------------------------" << endl;
	cout << "Materia examen e: " << e.getMaterie() << endl;
	cout << "Id examen e: " << e.getIdExamen() << endl;
	cout << "Data examenului e: ";
	for (int i = 0; i < 3; i++) {
		cout << e.getData()[i] << "/";
	}
	cout <<endl << "Nota e: " << e.getNota() << endl;
	cout << "Nr subiecte e: " << e.getNrSubiecte() << endl;
	cout << "Punctaj subiecte e: ";
	for (int i = 0; i < e.getNrSubiecte(); i++) {
		cout << e.getPunctajSubiecte()[i] << " | ";
	}
	cout << endl << endl;

	cout << "Materia examen e1: " << e1.getMaterie() << endl;
	cout << "Id examen e1: " << e1.getIdExamen() << endl;
	cout << "Profesor examen e1: " << e1.getProfesor() << endl;
	//cout << e.getData() << endl;//asa afisam adresa vectorului
	cout << "Data examenului e1: ";
	for (int i = 0; i < 3; i++) {
		cout << e1.getData()[i] << "/";

	}
	cout << endl;
	//cout << e1.materie << endl;		//inaccesibil (tip private)		=>> Getteri si Setter
	cout << "Nota e1: " << e1.getNota() << endl;
	cout << "Punctaj subiecte e1: ";
	for (int i = 0; i < e1.getNrSubiecte();) {
		cout << e1.getPunctajSubiecte()[i] << " | ";
		i++;
	}
	cout << endl << endl;

	cout << "------------------- Setteri---------------------------" << endl;
	e1.setMaterie("SO");
	cout << "Materia schimbata e1: " << e1.getMaterie() << endl;
	e1.setMaterie("Biologie");
	cout << "Materia schimbata e1: " << e1.getMaterie() << endl;
	
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
	//} while (nume.size() < 3);		//introduci pana cand numele > 3

	e.setNota(10);
	cout << "Nota (-1 nu e nota corecta): " << e.getNota() << endl;
	int dataNoua[3] = { 07, 07, 2021 };
	e1.setData(dataNoua);
	cout << "Data noua a examenului e1: ";
	for (int i = 0; i < 3; i++) {
		cout << e1.getData()[i] << "/";
	}
	cout << endl << endl;

	cout << "------------------- Constructor de copiere---------------------------" << endl;
	Examen e2 = e1;		//construc copiere
	//Examen e2(e1); -- ambele forme sunt corecte
	cout << "Materia examen e2: " << e2.getMaterie() << endl;
	cout << "Id examen e2: " << e2.getIdExamen() << endl;
	cout << "Nota examen e2: " << e2.getNota() << endl;
	cout << "Profesor examen e2: " << e2.getProfesor() << endl;

	e2.setNota(10);
	cout <<"Nota (-1 nu e nota corecta): "<< e2.getNota() << endl << endl;

	cout << "Punctaj subiecte e2: ";
	for (int i = 0; i < e2.getNrSubiecte();) {
		cout << e2.getPunctajSubiecte()[i] << " | ";
		i++;
	}
	cout << endl;
	//INT* FLOAT* => parcurse cu for si INDEXATE de i ([i])
	float pct1[] = { 12.3, 23.6, 23.56, 84, 21};
	e2.setPunctajSubiecte(5, pct1);

	cout << "Punctaj noi subiecte e2: ";
	for (int i = 0; i < 5; ) {
		cout << e2.getPunctajSubiecte()[i] << " | ";
		i++;
	}
	cout << endl;
	/*float pct2[] = {34.5, 345.6, 23.98, 10.23, 456.654 };
	e2.setPunctajSubiecte(5, pct2);
	cout << "Punctaj: ";
	for (int i = 0; i < 5; i++)
	{
		cout << e2.getPunctajSubiecte()[i] << " | ";
	}
	cout << endl;*/

	cout <<endl << "------------------- Operator = ---------------------------" << endl;
	Examen e3;
	e3 = e2;
	e1 = e1;
	float total = e1.totalPunctajeSubiect();
	cout << "Total punctaje examenul e1: " << total << endl << endl;
	
	cout << "Materia examen e3: " << e3.getMaterie() << endl;
	cout << "Id examen e3: " << e3.getIdExamen() << endl;
	cout << "Data examenului e3: ";
	for (int i = 0; i < 3; i++) {
		cout << e3.getData()[i] << "/";
	}
	cout << "Nota e3: " << e3.getNota() << endl;
	cout << "Nr subiecte e3: " << e3.getNrSubiecte() << endl;
	cout << "Punctaj subiecte e3: ";
	for (int i = 0; i < e3.getNrSubiecte(); i++) {
		cout << e3.getPunctajSubiecte()[i] << " | ";
	}
	cout << endl<< "-------------------Sfarsit Operator = ---------------------------" << endl;
	cout << endl<< "-------------------Metode ---------------------------" << endl;
	float min = e1.minPunctaje();
	cout << "cel mai mic punct e1: " << min << endl;
	float max = e3.maxPunctaje();
	cout << "cel mai mare punct e2: " << max << endl;

	if (e1.areRestanta())
	{
		cout << "Examenul a fost picat!" << endl;
	}
	else
	{
		cout << "Examenul a fost promovat!" << endl;
	}
	cout << "Punctaj vechi: ";
	for (int i = 0; i < e1.getNrSubiecte(); i++)
	{
		cout << e1.getPunctajSubiecte()[i] << " | ";

	}cout << endl;

	e1.adaugaSubiect(88);
	cout << e1.getNrSubiecte() << endl;
	cout << "Punctaj nou: ";
	for (int i = 0; i < e1.getNrSubiecte(); i++)
	{
		cout << e1.getPunctajSubiecte()[i] << " | ";

	}
	cout << endl <<endl;

	e1.eliminaSubiect(8.8);
	cout << "Eliminat 8.8 " << endl;
	cout << "Punctaj nou: ";
	for (int i = 0; i < e1.getNrSubiecte(); i++)
	{
		cout << e1.getPunctajSubiecte()[i] << " | ";

	}
	cout << endl;
	cout << endl << "-------------------Sfarsit Metode ---------------------------" << endl;
	cout << endl << "------------------Operatori ---------------------------" << endl;
	cout << e3 << endl<<endl;
	cout << e2 << endl;

	/*cin >> e;
	cout << endl << endl;
	cout << e << endl;
	*/
	cout << "Punctaj e1: ";
	for (int i = 0; i < e1.getNrSubiecte(); i++)
	{
		cout << e1.getPunctajSubiecte()[i] << " | ";

	}
	cout << endl <<"e1[2] = " << e1[2] << endl;		//op index - return this.punctaj[2]

	/*int poz;
	do
	{
		cout << "Introduceti pozitia dorita: ";
		cin >> poz;
		try {
			cout << e1[poz]<<endl;
		}
		catch (exception ex)
		{
			cout << "Pozitia introdusa este incorecta!" << endl;
		}
	} while (poz<0 || poz>= e1.getNrSubiecte());*/

	e3.setNota(5);
	int nota = e3(2);		// op functie 5 cu 2 7
	cout << nota << endl;

	cout << (string)e2 << endl;		//op cast explicit
	cout << endl << "------------------Operatori relationali ---------------------------" << endl;

	if (e1 < 3) {
		cout << "Examenul la " << e1.getMaterie() << "  are mai putin de 3 subiecte!" << endl;
	}
	else if (e2 < 3) {
		cout << "Examenul la " << e2.getMaterie() << "  are mai putin de 3 subiecte!" << endl;
	}
	else if (e3 < 3) {
		cout << "Examenul la " << e3.getMaterie() << "  are mai putin de 3 subiecte!" << endl;
	}
	else {
		cout << "Toate examenele au peste 3 subiecte." << endl;
	}

	if (e1 == e2) {
		cout << "Ambele examene sunt la acelasi profesor!" << endl;
	}
	else{
		cout << "Profi diferiti." << endl;
	}

	e2.setProfesor("Davidovici");
	if (e1 == e2) {
		cout << "Ambele examene sunt la acelasi profesor!" << endl;
	}
	else {
		cout << "Profi diferiti." << endl;
	}

	cout << endl;
	if (~e1)
	{
		cout << "Nu are restanta!" << endl;
		cout << e1.getNota() << endl;
	}
	else
	{
		cout << "Are restanta!" << endl;
		cout << e1.getNota() << endl;
	}
	if (!e1)
	{
		cout << "Nu are restanta!" << endl;
		cout << e1.getNota() << endl;
	}
	else
	{
		cout << "Are restanta!" << endl;
		cout << e1.getNota() << endl;
	}

	cout << "-------------------Operator ++ post si pre ---------------------------" << endl;
	e3 = e1++;
	cout << e3 << endl << endl;
	cout << e1 << endl << endl;

	Examen e4 = ++e1;
	cout << e4 << endl << endl;
	cout << e1 << endl << endl;
	cout << "-------------------Operator += si -= ---------------------------" << endl;
	e1 += 40;
	cout << e1 << endl;
	e1 -= 40;
	cout << e1 << endl;
	cout << "-------------------Functie statica ---------------------------" << endl;
	Examen vectExam[4];
	vectExam[0] = e;
	vectExam[1] = e1;
	vectExam[2] = e2;
	vectExam[3] = e3;
	cout << Examen::medieNoteExamene(4, vectExam);

	cout << endl << "-------------------Sfarsit Operatori ---------------------------" << endl;

	cout << endl << "-------------------tutoring vineri ---------------------------" << endl;
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
