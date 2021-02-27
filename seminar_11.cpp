#include <iostream>
#include<fstream>
using namespace std;

//functie template care aduna doua valori
template <class T>
T suma(T a, T b)
{
	return a + b;  //functioneaza pe oricare tip de data atata timp cat operatorul plus e supraincarcat pe acelasi tip de data astfel incat sa returneze tot p 
}
template <typename T1, typename T2>
bool egal(T1 x, T2 y)
{
	return x == y;  //aceasta functie va merge pe tipuri de date diferite care suporta egal, short si long spre exemplu nu merge pe char* si int
}

class student
{
public:
	int id = -1;
	char nume[100] = { "" }; //acesata e vector static de caractere si e ok pentru ca mereu ocupa acelasi nr de caractere
	int matricol = 0;
	float medie = 0; //daca pun si char* nume nu va merge serialirizarea si nici string nu merge dar daca vreau sa pun nume pun un char normal 
};


class student_voluntar : public student
{
public:
	string organizatie;
};

//the repository pattern 
//un repositary e o modalitate de a salva date unde am o operatie de tip crud(create, read, update, delete)
//facem un repository care permite lucrul cu obiecte de tip T astfel inca sa pot sa folosesc repository pentru orice tip de data
template <typename T>
class repository
{//vrem sa folosim fisiere binare ca o baza de date dar mult mai simplu decat la proiect 
	//o sa am un fisier binar la add
	//la citire o sa identific pentru tipul T sa aiba un ID
	//cum sa citim pe baza unui id avand un fisier binar care are studenti unul dupa altul
	//parcurg fisierul pana la final 

private:
	string filename;
public:
	repository(string filename)
	{
		this->filename = filename;
	}
	//functia nu are memebru poiter deci nu am nevoie de constructor de copiere, destructor etc
	//pentru clasa repository daca are membru pointer trebuie sa facem o specializare
	void add(T object)
	{
		//deschidem un fisier binar de iesire in mod app
		ofstream f(filename, ios::binary | ios::app);
		//scriem oniectul cu totul folosind metoda de a scrie binar intr-un fisier: write
		f.write((char*)&object, sizeof(object));
		f.close(); //inchidem fisier
	}
	T read(int id)
	{
		ifstream f(filename, ios::binary);
		T object;
		while (!f.eof())
		{
			f.read((char*)&object, sizeof(object));
			if (id == object.id)
			{
				f.close();
				return object;
			}
		}
		f.close();
		T newobject;
		return newobject;

	}
	void update(T object)
	{
		ifstream f(filename, ios::binary);
		ofstream g("temp.bin", ios::binary | ios::trunc);
		while (!f.eof())
		{
			T currentobject;
			f.read((char*)&currentobject, sizeof(currentobject));
			if (currentobject.id != -1)
			{
				if (currentobject.id == object.id)
				{
					g.write((char*)&object, sizeof(object));

				}
				else
					g.write((char*)&currentobject, sizeof(currentobject));
			}
		}
		f.close();
		g.close();
		remove(filename.c_str());
		int r = rename("temp.bin", filename.c_str());
	}
	void erase(int id)
	{
		ifstream f(filename, ios::binary);
		ofstream g("temp.bin", ios::binary | ios::trunc);
		while (!f.eof())
		{
			T object;
			f.read((char*)&object, sizeof(object));
			if (object.id != -1)
			{
				if (object.id != id)
				{
					g.write((char*)&object, sizeof(object));
				}
			}
		}
		f.close();
		g.close();
		remove(filename.c_str());
		int r = rename("temp.bin", filename.c_str());
	}

};
template<>
class repository<student_voluntar>
{

};




int main()
{
	cout << suma<int>(2, 3) << endl;  //in paranteze unghiulare e tipul adica T
	cout << suma<double>(2.5, 3.5) << endl;
	cout << egal<short, int>(1, 1) << endl;
	//egal<int*, int>(NULL, 1); nu poate sa compara int* cu int si da eroare de compilare 
	student s;
	strcpy_s(s.nume, "Vasile Ionescu");
	s.id = 2;
	s.matricol = 456;
	s.medie = 10;

	repository <student> repo("student.bin");
	//repo.add(s);
	//repo.update(s);
	repo.erase(2);
	student s2 = repo.read(1);
	student_voluntar v;
	/*v.id = 3;
	v.organizatie = "SISC";
	repository<student_voluntar> repo2("voluntar.bin");
	repo2.add(v);
	student_voluntar w = repo2.read(3); */
}