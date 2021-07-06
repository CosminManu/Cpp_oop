// examen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define _copy(dest, source) strcpy_s(dest, strlen(source) + 1, source)

using namespace std;

class Vector
{
    int elemente;
    double* vector;
    char* denumire;
public:
    static string tip;

    Vector() 
    {
        this->elemente = 0;
        this->vector = nullptr;
        this->denumire = nullptr;
    }

    Vector(int _elem, double* _vect, const char* _den)
    {
        if (_den != nullptr) {
            this->denumire = new char[strlen(_den) + 1];
            _copy(this->denumire, _den);
        }
        if (_vect != nullptr && _elem != 0) {
            this->elemente = _elem;
            this->vector = new double[_elem];
            for (int i = 0; i < _elem; i++) {
                this->vector[i] = _vect[i];
            }
        }
    }

    Vector(const Vector& v)
    {
        this->elemente = v.elemente; 
        if (this->vector != nullptr) {
            delete[] this->vector;
        }
        if (this->denumire != nullptr) {
            delete[] this->denumire;
        }
        this->vector = new double[v.elemente];
        for (int i = 0; i < v.elemente; i++) {
            this->vector[i] = v.vector[i];
        }
        this->denumire = new char[strlen(v.denumire) + 1];
        _copy(this->denumire, v.denumire);

    }

    ~Vector()
    {
        if (this->vector != nullptr) {
            delete[] this->vector;
        }
        if (this->denumire != nullptr) {
            delete[] this->denumire;
        }
    }

    char* getDenumire()
    {
        return this->denumire;
    }

    void setDenumire(char* _den)
    {
        if (_den != nullptr) {
            this->denumire = new char[strlen(_den) + 1];
            _copy(this->denumire, _den);
        }
    }

    explicit operator int()
    {
        return this->elemente;
    }

    double operator[](int poz) {
        if (poz > 0 && poz < this->elemente) {
            return this->vector[poz];
        }
    }

};

string Vector::tip = "double";

class Matrice 
{
    int linii;
    int col;
    Vector** vect;      //vect de adrese
public:
    Matrice()
    {
        this->linii = 0;
        this->col= 0;
        this->vect = nullptr;
    }

    Matrice(int _linii, int _col, Vector** v)
    {
        this->linii = _linii;
        this->col = _col;
        this->vect = new Vector * [this->linii];
        for (int i = 0; i < linii; i++)
        {
            this->vect[i] = new Vector(*v[i]);
        }
    }


};

int main()
{
    double elemente[3];
    for (int i = 0; i < 3; i++) {
        elemente[i] = i + 5;
    }
    Vector v1;
    Vector v2(3, elemente, "Intretineri");
    Vector v3 = v2;
    Vector v4 = v2;

    int x = (int)v2;
    cout << x << endl;

    int elem = v3[2];
    cout << elem << endl;

    Vector** v = new Vector * [3];
    v[0] = &v4;
    v[1] = &v2;
    v[2] = &v3;
    Matrice m(3, 3, v);

  



}

