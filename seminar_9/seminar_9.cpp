#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

class null_exception : public exception
{
public:
	null_exception()
	{

	}
	null_exception(const char* message) : exception(message)
	{

	}
};

class student
{
private:
	string grupa = "1050";
	int nr_matricol;
	int* note;
	int nr_note;
	char* adresa = nullptr;
	const int aniDeStudiu;
	static string universitate;

public:
	string nume;
	int varsta;

	student() : aniDeStudiu(3)
	{
		nume = "anonim";
		varsta = 18;
		nr_matricol = 0;
		note = nullptr;
		nr_note = 0;
	}

	student(string n, int v, string g, int aniDeStudiu)
		: note(nullptr), nr_note(0), aniDeStudiu(aniDeStudiu)
	{
		nume = n;
		grupa = g;
		if (v > 0)
		{
			varsta = v;
		}
		else
		{
			varsta = 18;
		}
	}

	student(string nume, const char* adresa)
		:student()
	{
		this->nume = nume;
		this->adresa = new char[strlen(adresa) + 1];
		strcpy_s(this->adresa, strlen(adresa) + 1, adresa);
	}

	student(string nume, int* note, int nr_note) 
		:student()
	{
		this->nume = nume;
		if (note != nullptr && nr_note > 0)
		{
			this->nr_note = nr_note;
			this->note = new int[nr_note];
			for (int i = 0; i < nr_note; i++)
			{
				this->note[i] = note[i];
			}
		}

	}

	student(const student& s) : aniDeStudiu(s.aniDeStudiu)
	{
		this->nume = s.nume;
		this->varsta = s.varsta;
		this->nr_matricol = s.nr_matricol;
		this->grupa = s.grupa;
		if (s.note != nullptr && s.nr_note != 0)
		{
			this->nr_note = s.nr_note;
			this->note = new int[s.nr_note];
			for (int i = 0; i < s.nr_note; i++)
			{
				this->note[i] = s.note[i];
			}
		}
		else
		{
			this->note = nullptr;
			this->nr_note = 0;
		}
		if (s.adresa != nullptr)
		{
			this->adresa = new char[strlen(s.adresa) + 1];
			strcpy_s(this->adresa, strlen(s.adresa) + 1, s.adresa);
		}
		else
		{
			this->adresa = nullptr;
		}
	}

	student& operator=(const student& s)
	{
		if (note != nullptr)
		{
			delete[] note;
		}
		if (adresa != nullptr)
		{
			delete[] adresa;
		}
		this->nume = s.nume;
		this->varsta = s.varsta;
		this->nr_matricol = s.nr_matricol;
		this->grupa = s.grupa;
		if (s.note != nullptr && s.nr_note != 0)
		{
			this->nr_note = s.nr_note;
			this->note = new int[s.nr_note];
			for (int i = 0; i < s.nr_note; i++)
			{
				this->note[i] = s.note[i];
			}
		}
		else
		{
			this->note = nullptr;
			this->nr_note = 0;
		}
		if (s.adresa != nullptr)
		{
			this->adresa = new char[strlen(s.adresa) + 1];
			strcpy_s(this->adresa, strlen(s.adresa) + 1, s.adresa);
		}
		else
		{
			this->adresa = nullptr;
		}
		return *this;
	}

	~student()
	{
		if (note != nullptr)
		{
			delete[] note;
		}
		if (adresa != nullptr)
		{
			delete[] adresa;
		}
	}

	void serializare()
	{
		ofstream f("student.bin", ios::binary);
		int length = nume.length();
		//pentru a scrie un sir de caractere, ii serializez mai intai dimensiunea
		f.write((char*)&length, sizeof(length));
		f.write(nume.c_str(), length + 1);
		f.write((char*)&varsta, sizeof(varsta));
		f.write((char*)&nr_matricol, sizeof(nr_matricol));
		//grupa o scriu ca atare, dar la serializare voi fi nevoit sa citesc byte cu byte
		f.write(grupa.c_str(), grupa.length() + 1);
		length = strlen(adresa);
		f.write((char*)&length, sizeof(length));
		f.write(adresa, length + 1);
		f.write((char*)&nr_note, sizeof(nr_note));
		for (int i = 0; i < nr_note; i++)
		{
			f.write((char*)&note[i], sizeof(note[i]));
		}
		f.close();
	}

	void deserializare()
	{
		ifstream f("student.bin", ios::binary);
		int length = 0;
		//citirea se face in aceeasi ordina ca scrierea
		f.read((char*)&length, sizeof(length));
		char* aux = new char[length + 1];
		f.read(aux, length + 1);
		nume = aux;
		delete[] aux;
		f.read((char*)&varsta, sizeof(varsta));
		f.read((char*)&nr_matricol, sizeof(nr_matricol));
		//citire caracter cu caracter si salvare in grupa
		grupa = "";
		char c = 0;
		while ((c = f.get()) != 0)	// != '\0'
		{
			grupa += c;
		}
		length = 0;
		f.read((char*)&length, sizeof(length));
		delete[] adresa;
		adresa = new char[length + 1];
		f.read(adresa, length + 1);
		f.read((char*)&nr_note, sizeof(nr_note));
		delete[] note;
		note = new int[nr_note];
		for (int i = 0; i < nr_note; i++)
		{
			f.read((char*)&note[i], sizeof(note[i]));
		}
		f.close();
	}

	bool operator!()		// negatie
	{
		return nr_note > 0;
	}

	student operator++()			// pre incremen
	{
		this->varsta++;
		return *this;
	}

	student operator++(int i)		// post increment
	{
		student copie = *this;
		this->varsta++;
		return copie;
	}

	student operator+(int valoare)		// op+ => obiect + valoare
	{
		if (valoare > 0)
		{
			student copie = *this;
			copie.varsta += valoare;
			return copie;
		}
		else
		{
			throw 15;
		}
	}

	int& operator[](int index)		// operator index
	{
		if (index >= 0 && index < nr_note)
		{
			return note[index];
		}
		throw exception("index invalid");
	}

	explicit operator int()		// cast explicit
	{
		return varsta;
	}

	int operator()()		// functie
	{
		if (adresa != nullptr)
		{
			return strlen(adresa);
		}
		else
		{
			throw null_exception();
		}
	}

	string getGrupa()
	{
		return grupa;
	}

	int getMatricol()
	{
		return nr_matricol;
	}

	void setMatricol(int nr_matricol)
	{
		if (nr_matricol > 0)
		{
			this->nr_matricol = nr_matricol;
		}
	}

	int* getNote()
	{
		if (note != nullptr)
		{
			int* copie = new int[nr_note];
			for (int i = 0; i < nr_note; i++)
			{
				copie[i] = note[i];

			}
			return copie;
		}
		else
		{
			return nullptr;
		}
	}

	int getNote(int index)
	{
		if (index >= 0 && index < nr_note && note != nullptr)
		{
			return note[index];
		}
	}

	int getNrNote()
	{
		return nr_note;
	}

	void setNote(int* note, int nr_note)
	{
		if (note != nullptr && nr_note != 0)
		{
			this->nr_note = nr_note;
			if (this->note != nullptr)
			{
				delete[] this->note;

			}
			this->note = new int[nr_note];
			for (int i = 0; i < nr_note; i++)
			{
				this->note[i] = note[i];
			}
		}
	}

	static string getUniversitate()
	{
		return universitate;
	}

	static void setUniversitate(string universitate)
	{
		student::universitate = universitate;
	}

	float punctaj_concurs()
	{
		float medie = 0;
		if (nr_note > 0 && note != nullptr) 
		{
			for (int i = 0; i < nr_note; i++) {
				medie += note[i];

			}
			medie = medie / nr_note;
		}
		return medie;
	}

	static float medieSerie(student* studenti, int nrStudenti)
	{
		float suma = 0;
		int nr = 0;
		if (studenti != nullptr && nrStudenti > 0)
		{
			for (int i = 0; i < nrStudenti; i++)
			{
				if (studenti[i].note != nullptr)
				{
					for (int j = 0; j < studenti[i].nr_note; j++)
					{
						suma += studenti[i].note[j];
						nr++;
					}
				}
			}
			if (nr > 0)
			{
				return suma / nr;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}

	float punctaj_concurs(int i)
	{
		float medie = student::punctaj_concurs();
		if (medie > 9) {
			return 10;
		}
		else return medie + 1;
	}

	void metoda() {
		cout << "Student" << endl;
	}

	friend ostream& operator<<(ostream&, student);
	friend istream& operator>>(istream&, student&);
};
string student::universitate = "ASE";

student operator+(int valoare, student s)	//obiect + valoare / val + obiect
{
	s.varsta += valoare;
	return s;
}

ostream& operator<<(ostream& out, student s)
{
	out << "nume: ";		// string
	out << s.nume << endl;

	out << "varsta: ";		// int
	out << s.varsta << endl;
	out << "matricol: ";	// int
	out << s.nr_matricol << endl;
	out << "grupa: ";		// string
	out << s.grupa << endl;
	out << "ani de studiu: ";
	out << s.aniDeStudiu << endl;	// const int
	out << "adresa: ";
	if (s.adresa != nullptr)
	{
		out << s.adresa;		// char*
	}
	else {
		out << "N/A";
	}
	out << endl;
	out << "numar note: ";
	out << s.nr_note << endl;		// int
	out << "note: ";
	if (s.note != nullptr)
	{
		for (int i = 0; i < s.nr_note; i++)
		{
			out << s.note[i] << " ";	// int*
		}
	}
	return out;
}

istream& operator>>(istream& in, student& s)
{
	cout << "nume = ";
	in >> ws;
	getline(in, s.nume);	// string (spatii libere)
	cout << "varsta = ";
	in >> s.varsta;		// int
	cout << "numar matricol = ";
	in >> s.nr_matricol; // int
	cout << "grupa = ";
	in >> s.grupa;      // string
	char buffer[100];
	cout << "adresa: ";
	in >> ws;

	in.getline(buffer, 99);
	if (s.adresa != nullptr)
	{
		delete[] s.adresa;		// char*
	}
	s.adresa = new char[strlen(buffer) + 1];
	strcpy_s(s.adresa, strlen(buffer) + 1, buffer);		// sau string buf si getline(in, buf) si strcpy_s(.., buf.length() + 1, buf.c_str());
	cout << "numar note = ";
	in >> s.nr_note;
	if (s.note != nullptr)
	{
		delete[] s.note;
	}
	//validare biti bad si fail stream de intrare
	if (in.good() && s.nr_note > 0)
	{
		s.note = new int[s.nr_note];
		for (int i = 0; i < s.nr_note; i++)
		{
			cout << "note[" << i << "] = ";
			in >> s.note[i];				// int*
		}
	}
	else
	{
		s.nr_note = 0;
		s.note = nullptr;
	}
	return in;
}

class voluntar
{
private:
	int nr_zile = 0;
	int* ore_zilnice = nullptr;

public:
	voluntar()
	{

	}
	voluntar(int nr_zile, int* ore_zilnice) {
		if (ore_zilnice != nullptr && nr_zile != 0) {
			this->nr_zile = nr_zile;
			this->ore_zilnice = new int[nr_zile];
			for (int i = 0; i < nr_zile; i++) {
				this->ore_zilnice[i] = ore_zilnice[i];
			}
		}
	}

	

	voluntar(const voluntar& v)
	{
		if (v.ore_zilnice != nullptr && v.nr_zile > 0) {
			this->nr_zile = v.nr_zile;
			this->ore_zilnice = new int[nr_zile];
			for (int i = 0; i < v.nr_zile; i++) 
			{
				this->ore_zilnice[i] = v.ore_zilnice[i];
			}
		}
	}

	voluntar operator=(const voluntar& v) {
		if (ore_zilnice != nullptr) {
			delete[]ore_zilnice;
		}
		if (v.ore_zilnice != nullptr && v.nr_zile > 0) {
			this->nr_zile = v.nr_zile;
			this->ore_zilnice = new int[nr_zile];
			for (int i = 0; i < v.nr_zile; i++) {
				this->ore_zilnice[i] = v.ore_zilnice[i];
			}
		}
		else {
			nr_zile = 0;
			ore_zilnice = nullptr;
		}
		return *this;
	}

	~voluntar() {
		if (ore_zilnice != nullptr) {
			delete[]ore_zilnice;
			ore_zilnice = nullptr;
		}
	}

	void metoda() {
		cout << "Voluntar" << endl;
	}
};

class student_voluntar : public student,public voluntar
{
private:
	char* organizatie = nullptr;

public:
	student_voluntar()
	{
		organizatie = new char[strlen("necunoscuta") + 1];
		strcpy_s(organizatie, strlen("necunoscuta") + 1, "necunoscuta");
	}


	student_voluntar(string nume, int* note, int nr_note, const char* organizatie) 
		:student(nume, note, nr_note)
	{
		if (organizatie != nullptr)
		{
			this->organizatie = new char[strlen(organizatie) + 1];
			strcpy_s(this->organizatie, strlen(organizatie) + 1, organizatie);
		}
	}

	student_voluntar(string nume, const char* adresa, 
		int nr_zile, int* ore_zilnice, const char* organizatie)
		:student(nume,adresa), voluntar(nr_zile,ore_zilnice)
	{
		if (organizatie != nullptr)
		{
			this->organizatie = new char[strlen(organizatie) + 1];
			strcpy_s(this->organizatie, strlen(organizatie) + 1, organizatie);
		}
	}

	~student_voluntar()
	{
		if (organizatie != nullptr)
		{
			delete[] organizatie;
		}
	}

	student_voluntar(const student_voluntar& s) 
		:student(s),voluntar(s)
	{
		if (s.organizatie != nullptr)
		{
			this->organizatie = new char[strlen(s.organizatie) + 1];
			strcpy_s(this->organizatie, strlen(s.organizatie) + 1, s.organizatie);

		}
	}

	student_voluntar operator=(const student_voluntar& s)
	{
		student::operator=(s);
		voluntar::operator=(s);
		if (organizatie != nullptr)
		{
			delete[] organizatie;
		}

		if (s.organizatie != nullptr)
		{
			this->organizatie = new char[strlen(s.organizatie) + 1];
			strcpy_s(this->organizatie, strlen(s.organizatie) + 1, s.organizatie);

		}
		return *this;
	}

	void metoda() 
	{
		student::metoda();
	}
	friend ostream& operator<<(ostream&, student_voluntar);
	friend istream& operator>>(istream&, student_voluntar&);
	friend ofstream& operator<<(ofstream&, student_voluntar);
	friend ifstream& operator>>(ifstream&, student_voluntar&);
};

ostream& operator<<(ostream& out, student_voluntar s)
{
	out << (student)s << endl;
	if (s.organizatie != nullptr)
		out << "organizatie:" << s.organizatie;
	return out;
}

istream& operator>>(istream& in, student_voluntar& s)
{
	in >> (student&)s;
	string buffer;
	cout << "organizatie = ";
	in >> ws;
	getline(in, buffer);
	if (s.organizatie != nullptr)
		delete[] s.organizatie;
	s.organizatie = new char[buffer.length() + 1];
	strcpy_s(s.organizatie, buffer.length() + 1, buffer.c_str());
	return in;
}

ofstream& operator<<(ofstream& out, student_voluntar s)
{
	out << (student)s << endl;
	if (s.organizatie != nullptr)
		out << s.organizatie;
	else
	{
		out << "N/A";
	}
	return out;
}

ifstream& operator>>(ifstream& in, student_voluntar& s)
{
	in >> (student&)s;
	string buffer;
	in >> ws;
	getline(in, buffer);
	if (s.organizatie != nullptr)
		delete[] s.organizatie;
	s.organizatie = new char[buffer.length() + 1];				// char*
	strcpy_s(s.organizatie, buffer.length() + 1, buffer.c_str());
	return in;
}

int main()
{
	student s;
	s.nume = "Ion Popescu";
	cout << "Nume elev: " << s.nume << endl;
	cout << "Varsta " << s.varsta << endl;

	student* ps;
	ps = &s;
	cout << "======== Pointer la student ============" << endl;
	cout << (*ps).nume << endl;
	cout << ps->nume << endl;
	cout << "Marimea obiectului s " << sizeof(s) << endl;
	student s2 = s;
	cout << "Marimea obiectului s2 " << sizeof(s2) << endl;

	cout << endl;
	ps = new student();
	cout << ps->nume << endl;
	delete ps;

	student s3("Maria Popescu", 20, "1054", 2);
	cout << s3.nume << endl;

	student s4("Vasile Musat", "Str Ion Creanga, nr 8");
	cout << s4.nume << endl;

	student vector[3];

	student* ps2 = new student("Marcel Ionascu", "Str Avionului, nr 4");
	cout << ps2->nume << endl;
	delete ps2;

	int note[] = { 7,4,9 };

	cout << endl;
	student s5("Dan", note, 3);
	student s6(s5);

	cout << s.getGrupa() << endl;

	s6.setMatricol(5);
	cout <<"NUmar matricol "<< s6.getMatricol() << endl;

	int z[] = { 1,2,3,4,5 };
	s6.setNote(z, 5);
	int* n = s6.getNote();

	cout << "Note: ";
	for (int i = 0; i < s6.getNrNote(); i++)
	{
		cout << n[i] << " ";
	}
	cout << endl;

	delete[] n;
	n = nullptr;

	cout << "Schimbarea atribut static in Politehn" << endl;
	student::setUniversitate("Politehnica");
	cout << s.getUniversitate() << endl;
	cout << s5.getUniversitate() << endl;
	cout << student::getUniversitate() << endl;

	student studenti[] = { s5, s6 };				// apeleaza const copiere pt s5 si s6 => studenti[]
	float medie = student::medieSerie(studenti, 2);
	cout << medie << endl;

	cout << endl;
	student s7 = s5;
	s = s6;
	s = s5 = s6;
	bool areNote = !s5;
	cout << areNote << endl;
	student s8 = ++s5;
	student s9 = s6++;

	s8 = s5 + 7;
	s9 = 3 + s5;

	cout << s5 << endl;
	student s10;
	//cin >> s10;
	//cout << s10 << endl;
	//s5[1] = 10;
	//cout << s5[1] << endl;

	int varsta = (int)s9;
	cout << varsta << endl;
	cout << s4();

	student_voluntar sv1;
	student_voluntar sv2("Andrei", z, 5, "SISC");
	student_voluntar sv3 = sv2;
	sv1 = sv2;

	cin >> sv1;
	cout << sv1;

	student cs = sv1;
	//tratare exceptii
	try
	{
		sv2 + 2;
		s10();
		cout << sv2[2];
	}
	catch (null_exception e)
	{
		cout << "obiect nul";
	}
	catch (exception e)
	{
		cout << e.what();
	}
	catch (int i)
	{
		cout << "cod eroare: " << i;
	}
	catch (...)
	{
		cout << "alta eroare";
	}

	cout << endl << setw(6) << setfill('#') << hex << setiosflags(ios::left | ios::showbase) << s2.varsta << endl;
	cout << dec << resetiosflags(ios::left | ios::showbase);

	ofstream f;
	f.open("student.txt");
	f << s5;
	f.close();

	ifstream g("student.txt");
	student s12;
	g >> s12;
	g.close();

	ofstream h("student_voluntar.txt");
	h << sv2;
	h.close();

	ifstream k("student_voluntar.txt");
	student_voluntar sv6;
	k >> sv6;
	k.close();

	s4.setNote(note, 3);
	s4.serializare();

	student s14;
	s14.deserializare();

	//citire ultim element din fisier binar
	fstream fisier("student.bin", ios::binary | ios::in);
	//ne deplasam de la sfarsitul fisierului 4 bytes inapoi
	fisier.seekg(-4, ios::end);
	//citim 4 bytes (ultimul element din vector)
	int element = 0;
	fisier.read((char*)&element, sizeof(int));
	cout << endl << "element = " << element;
	fisier.close();


	voluntar v1;
	int ore[] = { 1,2,3 };
	voluntar v2(3, ore);
	voluntar v3 = v2;	// const copiere
	v1 = v2;			// operat= (v1 exista deja)

	cout << endl;
	sv1.student::metoda();
	sv1.student_voluntar::metoda();

	student stud;
	int valori[] = { 8,8,9 };
	stud.setNote(valori, 3);
	cout << stud.punctaj_concurs() << endl;
	
	student_voluntar stud_v;
	stud_v.setNote(valori, 3);
	cout << stud_v.punctaj_concurs() << endl;

	stud = stud_v;
	cout << stud.punctaj_concurs() << endl;

	student& r_stud = stud;
	cout << endl;

}