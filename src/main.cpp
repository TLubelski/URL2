#include "common.hh"
#include "Wektor.hh"
#include "MacierzKw.hh"
#include "UklRowL.hh"

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

typedef Wektor<double, _ROZMIAR> WektC;
typedef UklRowL<double, _ROZMIAR> UklC;

typedef Wektor<LZ,_ROZMIAR> WektZ;
typedef UklRowL<LZ, _ROZMIAR> UklZ;

int main()
{   

    //***********DOUBLE********
    
    UklC uklad_rownan;
    //wczytanie z pliku
    fstream plik_dane;
    plik_dane.open("daneC.dat", ios::in);
    if (!plik_dane.good())
    {
        cerr << "[!]Niepoprawny plik" << endl;
        exit(1);
    }
    plik_dane >> uklad_rownan;

    //wyswietlenie
    cout << "---------Uklad rownan calkowity-----------" << endl;
    cout << fixed << setprecision(2);
    cout << uklad_rownan;
    //wyswietlenie wyniku
    cout << endl
         << "Wynik:  " << uklad_rownan.oblicz() << endl;

    WektC blad = uklad_rownan.wekt_bledu();
    cout << scientific << setprecision(1);
    cout << endl
         << "Wektor bledu:  " << blad << endl;
    cout << "Jego dlugosc:  " << blad.dlugosc() << endl;

    //zamkniecie pliku
    plik_dane.close();
    
    cout << endl << endl;
    
    //*************LZ******************
    
    UklZ uklad_rownanZ;
    //wczytanie z pliku
    fstream plik_daneZ;
    plik_daneZ.open("daneLZ.dat", ios::in);
    if (!plik_daneZ.good())
    {
        cerr << "[!]Niepoprawny plik" << endl;
        exit(1);
    }
    plik_daneZ >> uklad_rownanZ;

    //wyswietlenie
    cout << "---------Uklad rownan zespolony-----------" << endl;
    cout << fixed << setprecision(2);
    cout << uklad_rownanZ;

    //wyswietlenie wyniku
    cout << endl
         << "Wynik:  " << uklad_rownanZ.oblicz() << endl;

    WektZ bladZ = uklad_rownanZ.wekt_bledu();
    cout << scientific << setprecision(1);
    cout << endl
         << "Wektor bledu:  " << bladZ << endl;
    cout << "Jego dlugosc:  " << bladZ.dlugosc() << endl;

    //zamkniecie pliku
    plik_daneZ.close();

}
