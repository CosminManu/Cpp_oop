#include<iostream>
#define NULL 0

using namespace std;

static int var = 99;
static int v[] = { 0, 5, 7, 9, 12, 99, 100 };

//Handout 1
//ATENTIE!!!
//Sunt punctate doar solutiile originale si individuale
//Orice incercare de frauda va duce la pierderea intregului punctaj de la seminar
//Signatura functiilor nu se poate modifica, doar continului lor

//1. Pentru a testa proiectul de teste unitare, scrieti corpul aceste functii
//astfel incat sa returneze corect suma dintre parametrii x si y
long suma(int x, int y)
{
	return x + y;
}

//2. Definiti un pointer la float si initializati-l cu NULL
//returnati acest pointer
float* returnare_pointer_null()
{
	float* p = NULL;
	return p;
}

//3. Definiti un pointer la int si initializati-l cu adresa
//variabilei globale variabila, returnati acest pointer
int* returnare_pointer_adresa()
{
	int* ptr = &var;
	return ptr;
}

//4. Functia de mai jos primeste ca si parametru un pointer la double
//returnati valoarea aflata la acea adresa
double returnare_valoare_de_la_adresa(double* pointer)
{
	return *pointer;
}

//5. Functia de mai jos primeste ca si parametru un pointer la int
//returnati adresa urmatorului intreg utilizand operatori specifici pointerilor
int* returnare_adresa_intreg_urmator(int* pointer)
{
	return (pointer + 1);		//adresa urm pointer la intreg

}

//6. Functia de mai jos primeste ca si parametru un pointer la long
//returnati valoarea de la adresa mai mica cu 2 * sizeof(long) fata de aceasta
//utilizand operatori specific pointerilor
long returnare_adresa_long_precedent(long* pointer)
{
	return *(pointer - 2);		//nu mai e nev de sizeof(), el stie ca e long
}

//7. Functia de mai jos primeste ca si parametrii 2 pointeri la int
//returnati numarul de intregi care incap intre cele doua adrese de memorie
//8. Asigurati-va ca rezultatul este tot timpul unul pozitiv
int returnare_diferenta(int* p1, int* p2)
{
	int n = 0;
	if (p1 > p2) {
		n = p1 - p2;
	}
	else if (p1 < p2) {
		n = p2 - p1;
	}
	
	return n;
}

//9. Functia de mai jos primeste ca si parametru un pointer la pointer la int
//acesta reprezinta adresa unei adrese la care se gaseste un intreg
//returnati acel intreg
int returnare_valoare_adresa_de_adresa(int** pointer)
{
	return *(*pointer);
}

//10. Functia de mai jos este similara functiei de mai sus cu o mica diferenta
//all doilea parametru ne spune tipul de pointer => I pentru intreg sau L pentru long
//transformati pointerul primit ca parametru in tipul corespunzator
//si apoi returnati valoarea obtinuta la fel ca in functia de mai sus
long returneaza_valoarea_adresa_de_adresa_void(void** pointer, char tip_pointer)
{
	if (tip_pointer == 'I') {
		return **(int**)pointer;
	}
	else if (tip_pointer == 'L') 
	{
		long p = **(long**)pointer;
		return p;
	}
}

//Handout 2
//1. v este un vector global alocat static
//returnati numarul de elemente al acestui vector
int nr_elem() 
{
	/*int nr = 0;
	for (int i = 0; i<v) {

	}*/
	return 0;
}

//2. Functia de mai jos returneaza maximul dintr-un vector
//alocat dinamic primit ca parametru (alaturi de dimensiune)
//daca vectorul este null sau dimensiunea <= 0
//atunci functia returneaza 0
float maxim_vector(float* vector, int dimensiune)
{
	float max = 0.0f;
	if (vector != nullptr && dimensiune > 0) {
		max = *vector;
		for (int i = 0; i < dimensiune; i++)
		{
			if (max < *(vector + i)) {
				max = *(vector + i);
			}
		}
		return max;
	}
	else
	{
		return 0;
	}
}

//3. Returnati o copie a vectorului de caractere
//primit drept parametru
char* returnare_copie_vector_caractere(const char* sir)
{
	/*char* sir2 = new char[strlen(sir) + 1];
	if (sir != nullptr) {
		for (int i = 0; i < strlen(sir); ) {
			sir2[i] = sir[i];
			i++;
		}
	}*/
	char* sir2 = new char[strlen(sir) + 1];
	strcpy_s(sir2, strlen(sir) + 1, sir);
	return sir2;
}

//5. Functia de mai jos primeste ca si parametrii un string si un char*
//si returneaza true daca cele doua siruri de caractere au acelasi continut
bool siruri_egale(string sir1, char* sir2)
{
	if (sir1 == sir2) {		//indiferent ca e string si char*
		return true;
	}
	else return false;
}

//6. Functia de mai jos primeste ca si parametri o matrice alocata dinamic,
//precum si numarul de linii si de coloane
//functia returneaza true daca matricea primita ca parametru este matrice unitate
//(este patratica, iar pe diagonala principala are doar 1, iar restul elementelor sunt 0)
bool matrice_unitate(int** matrice, int linii, int coloane)
{
	if (linii == coloane) {
		for (int i = 0; i < linii; i++) {
			for (int j = 0; j < coloane; j++) {
				if ( (matrice[i][i] == 1) && (matrice[i][j] == 0) ){
					return true;
				}
			}
		}
	}

}
int main()
{
	double p = 10.1;
	double* ptr = &p;

	double x = returnare_valoare_de_la_adresa(ptr);
	cout << x << endl;

	int scores[] = {100, 55, 89};		//vector de 3 elem
	int* p_5 = scores;				//fara &scores
	int* ex5 = returnare_adresa_intreg_urmator(p_5);		//la fiecare rulare se afis alte adrese de mem
	cout << ex5 << endl;

	cout << *(p_5 + 1);		//55  - val adresa intreg urmator

	cout << endl << endl;
	float ex2_h2[] = { 11.23, 2500.5, 345.34 };
	float* pt2 = ex2_h2;

	float max = maxim_vector(pt2, 3);
	cout << max << endl;

	char sir[20] = "Manu Cosmin";
	char* nume = sir;
	char* copie = returnare_copie_vector_caractere(nume);
	cout << *copie << endl;				// returneaza PRIMA LITERA (M)

	for (int i = 0; i < strlen(copie); i++) {
		cout << copie[i];
	}

	cout << endl;
	string nume2 = "Manu Cosmin";
	bool b = siruri_egale(nume2, nume);
	cout <<"Sirurile egale: "<< b <<endl;

	
}


