// 2021_vaccinuri.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#define _copy(dest, source) strcpy_s(dest, strlen(source) + 1, source)

using namespace std;

class Vaccin 
{
    const int idVaccin;
    static int serie;
protected:
    char* producator;
    char* taraProv;
    int capacitate;
    float tempTransport;
    string denumire;
    int dataExpirarii[3];
public:
    Vaccin() :idVaccin(serie++)
    {
        this->producator = new char[strlen("N/A") + 1];
        _copy(this->producator, "N/A");
        this->taraProv = new char[strlen("Necunoscut") + 1];
        _copy(this->taraProv, "Necunoscut");
        
        this->capacitate = 0;
        this->tempTransport = 0.0f;
        this->denumire = "Necunoscut";
        for (int i = 0; i < 3; i++) {
            this->dataExpirarii[i] = 1;
        }
    }

    Vaccin(const char* _producator, const char* _tara, int _cap, float _temp, string _den, int _data[3]) 
        :idVaccin(serie++)
    {
        this->producator = new char[strlen(_producator) + 1];
        _copy(this->producator, _producator);
        this->taraProv = new char[strlen(_tara) + 1];
        _copy(this->taraProv, _tara);
        this->capacitate = _cap;
        this->tempTransport = _temp;
        this->denumire = _den;
        for (int i = 0; i < 3; i++) {
            this->dataExpirarii[i] = _data[i];
        }
    }

    //cons copiere
    Vaccin(const Vaccin& vac) : idVaccin(vac.serie)
    {
        this->producator = new char[strlen(vac.producator) + 1];
        _copy(this->producator, vac.producator);
        this->taraProv = new char[strlen(vac.taraProv) + 1];
        _copy(this->taraProv, vac.taraProv);
        this->capacitate = vac.capacitate;
        this->tempTransport = vac.tempTransport;
        this->denumire = vac.denumire;
        for (int i = 0; i < 3; i++) {
            this->dataExpirarii[i] = vac.dataExpirarii[i];
        }
    }


    const int getId()
    {
        return this->idVaccin;  //constant pt acel ob creat
    }

    char* getProducator()
    {
        if (this->producator != nullptr) {
            return this->producator;
        }
        else return nullptr;
    }

    void setProducator(const char* _prod)
    {
        if (_prod != nullptr) {
            if (this->producator != nullptr) {
                delete[] this->producator;
                this->producator = new char[strlen(_prod) + 1];
                _copy(this->producator, _prod);
            }
        }
    }

    void setDataExpirarii(int _data[3])
    {
        if (_data[0] > 1 && _data[0] <= 31 && _data[1] > 1 && _data[1] <= 12)
        {
            for (int i = 0; i < 3; i++) {
                this->dataExpirarii[i] = _data[i];
            }
        }
    }

    int* getData()
    {
        return this->dataExpirarii;
    }
    
    //destruct - dezaloc mem heap
    //sterg explicit pointerii
    ~Vaccin()
    {
        if (this->producator != nullptr) {
            delete[] this->producator;
        }
        if (this->taraProv != nullptr) {
            delete[] this->taraProv;
        }
    }
    
    //op= : destruc + cons copi + return *this
    Vaccin& operator=(const Vaccin& src)
    {
        if (this != &src)   //evitarea auto asignarii
        {
            if (this->producator != nullptr) {
                delete[] this->producator;
            }
            if (this->taraProv != nullptr) {
                delete[] this->taraProv;
            }
            this->producator = new char[strlen(src.producator) + 1];
            _copy(this->producator, src.producator);
            this->taraProv = new char[strlen(src.taraProv) + 1];
            _copy(this->taraProv, src.taraProv);
            this->capacitate = src.capacitate;
            this->tempTransport = src.tempTransport;
            this->denumire = src.denumire;
            for (int i = 0; i < 3; i++) {
                this->dataExpirarii[i] = src.dataExpirarii[i];
            }
            return *this;
        }
    }

    friend istream& operator>>(istream&, Vaccin&);       //citire (cin >>)
    friend ostream& operator<<(ostream&, const Vaccin);        //afisare (cout <<)
};

ostream& operator<<(ostream& out, const Vaccin v)
{
    out << "Producator: " << v.producator << endl;
    out << "Tara provenienta: " << v.taraProv << endl;
    out << "Capacitate: " << v.capacitate << endl;
    out << "Temperatura transport: " << v.tempTransport << endl;
    out << "Denumire: " << v.denumire << endl;
    cout << "Data expirarii: ";
    for (int i = 0; i < 3; i++) {
        cout << v.dataExpirarii[i]<<".";
    }
    cout << endl;

    return out;
}


//char* producator;
//char* taraProv;
//int capacitate;
//float tempTransport;
//string denumire;
//int dataExpirarii[3];
//intai dezaloca pointerii si apoi aloca iar
istream& operator>>(istream& i, Vaccin& v)
{
    if (v.producator != nullptr) {
        delete[] v.producator;
    }
    if (v.taraProv != nullptr) {
        delete[] v.taraProv;
    }

    //ca la fisiere!
    cout << "Producator: ";
    i >> ws;
    char buf[30];
    i.getline(buf, 29);
    v.producator = new char[strlen(buf) + 1];
    _copy(v.producator, buf);

    cout << "Tara productie: ";
    i >> ws;
    char buf1[30];
    i.getline(buf1, 29);
    v.taraProv = new char[strlen(buf1) + 1];
    _copy(v.taraProv, buf1);

    cout << "Capacitate: ";
    i >> v.capacitate;

    cout << "Temperatura transport: ";
    i >> v.tempTransport;

    cout << "Denumire vaccin: ";
    i >> v.denumire;

    cout << "Data expirarii (z.l.an): ";
    for (int j = 0; j < 3; j++) {
        i >> v.dataExpirarii[j];        //se da enter
    }

    return i;
}

int Vaccin::serie = 8800;

class VaccinRubeola : public Vaccin
{
    int bucati;
    string cercetator;

public:
    VaccinRubeola():Vaccin()
    {
        this->bucati = 0;
        this->cercetator = "N/A";
    }

    VaccinRubeola(const char* _producator, const char* _tara, int _cap, float _temp, string _den, int _data[3], int _buc, string _cercet)
        :Vaccin(_producator, _tara, _cap, _temp, _den, _data)
    {
        this->bucati = _buc;
        this->cercetator = _cercet;
    }

    VaccinRubeola(const VaccinRubeola& v)
        :Vaccin(v)
    {
        this->bucati = v.bucati;
        this->cercetator = v.cercetator;
    }

    ~VaccinRubeola()
    {
    }

    VaccinRubeola& operator=(const VaccinRubeola& src)
    {
        Vaccin::operator=(src);             //apel op+ din clasa baza
        this->bucati = src.bucati;
        this->cercetator = src.cercetator;
        return *this;
    }

};


int main()
{
    int data1[3] = {12, 06, 2020};
    Vaccin v1;
    Vaccin v2("Moderna","Spania", 20, 2.7, "ModVacc", data1);

    char* p = new char[30];
    p = v2.getProducator();
    cout << p << endl;

    v1.setProducator("BioNTec");
    cout << v1.getProducator() << endl;

    int data2[3] = { 30, 04, 2019 };
    v2.setDataExpirarii(data2);

    cout << "Data expirarii v2: ";
    for (int i = 0; i < 3; i++) {
        cout << v2.getData()[i] << ".";
    }

    Vaccin v3;
    v3 = v2;

    Vaccin v4;
    cout << endl;
    cin >> v4;
    cout << v4;

    VaccinRubeola vr1();

}
