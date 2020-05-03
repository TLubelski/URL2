#include "Wektor.hh"

#include <cmath>
#include <regex>
#include <sstream>

using namespace std;

/*KONSTRUKTORY*/

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR>::Wektor()
{
    for (int i = 0; i < ROZMIAR; i++)
        tab[i] = 0;
    
}


template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR>::Wektor(TYP *tab)
{
    for (int i = 0; i < ROZMIAR; i++)
        this->tab[i] = tab[i];
}


/*OPERATORY*/
template <typename TYP, int ROZMIAR>
const TYP & Wektor<TYP, ROZMIAR>::operator[](int index) const
{
    if (index < 0 || index >= ROZMIAR)
    {
        cerr << "[!] Index out of range in Wektor" << endl;
        exit(1);
    }
    return tab[index];
}

template <typename TYP, int ROZMIAR>
TYP & Wektor<TYP, ROZMIAR>::operator[](int index)
{
    if (index < 0 || index >= ROZMIAR)
    {
        cerr << "[!] Index out of range in Wektor" << endl;
        exit(1);
    }
    return tab[index];
}

template <typename TYP, int ROZMIAR>
bool Wektor<TYP, ROZMIAR>::operator==(const Wektor &W2) const
{
    bool wynik = true;
    for (int i = 0; i < ROZMIAR; i++)
    {
        if ( !cmp(tab[i], W2.tab[i]) )
            wynik = false;
    }
    return wynik;
}

template <typename TYP, int ROZMIAR>
bool Wektor<TYP, ROZMIAR>::operator!=(const Wektor &W2) const
{
    return !(*this == W2);
}

template <typename TYP, int ROZMIAR>
Wektor<TYP,ROZMIAR> Wektor<TYP, ROZMIAR>::operator+(const Wektor &W2) const
{
    Wektor temp;
    for (int i = 0; i < ROZMIAR; i++)
        temp.tab[i] = tab[i] + W2.tab[i];
    return temp;
}

template <typename TYP, int ROZMIAR>
const Wektor<TYP, ROZMIAR> & Wektor<TYP, ROZMIAR>::operator+=(const Wektor &W2)
{
    *this = *this + W2;
    return *this;
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR> Wektor<TYP, ROZMIAR>::operator-(const Wektor &W2) const
{
    Wektor temp;
    for (int i = 0; i < ROZMIAR; i++)
        temp.tab[i] = tab[i] - W2.tab[i];
    return temp;
}

template <typename TYP, int ROZMIAR>
const Wektor<TYP, ROZMIAR> & Wektor<TYP, ROZMIAR>::operator-=(const Wektor &W2)
{
    *this = *this - W2;
    return *this;
}

template <typename TYP, int ROZMIAR>
TYP Wektor<TYP, ROZMIAR>::operator*(const Wektor &W2) const //iloczyn skalarny
{
    TYP temp;
    for (int i = 0; i < ROZMIAR; i++)
    {
        temp += tab[i] * W2.tab[i];
    }
    return temp; 
}

/*API*/

template <typename TYP, int ROZMIAR>
double Wektor<TYP, ROZMIAR>::dlugosc() const
{
    double suma;
    suma = 0;
    for (int i = 0; i < ROZMIAR; i++)
        suma += tab[i] * tab[i];
    return sqrt(suma);
    return suma;
}

/*Specjalizacja dlugosci dla LZ*/
template <>
double Wektor<LZ, _ROZMIAR>::dlugosc() const
{
    double suma = 0;
    LZ temp;
    
    for (int i = 0; i < _ROZMIAR; i++)
    { 
        temp = tab[i] * tab[i].sprzez();
        suma += temp.getRe();
    }

    return sqrt(suma);
}


/*OPERATORY ZEWNETRZNE*/

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR> operator*(TYP l1, const Wektor<TYP, ROZMIAR> W2) //mnozenie przez liczbe
{
    Wektor<TYP,ROZMIAR> temp;
    for (int i = 0; i < ROZMIAR; i++)
        temp[i] = W2[i] * l1;
    return temp;
}

template <typename TYP, int ROZMIAR>
ostream & operator<<(ostream &strm, const Wektor<TYP,ROZMIAR> &W)
{
    strm << "|";
    for(int i = 0; i < ROZMIAR-1; i++)
        strm << W[i] << " ";
    
    strm << W[ROZMIAR-1];
    strm << "|";    

    return strm;
}

template <typename TYP, int ROZMIAR>
istream & operator>>(istream &strm, Wektor<TYP,ROZMIAR> &W)
{
    string wzor_s = "\\|";
    string liczba = "\\-?\\d+.?\\d*";

    //zbudowanie wzoru regexa o odpowienim rozmiarze
    for (int i = 0; i < ROZMIAR - 1; i++)
    {
        wzor_s += liczba;
        wzor_s += "\\s";
    }
    wzor_s += liczba;
    wzor_s += "\\|";
    regex wzor(wzor_s); //inicjalizacja walasciwego regexa

    //oczyt ze strumienia
    stringstream ss;
    string input;
    smatch wynik;
    getline(strm, input);
    ss << input;

    char trash;
    if (regex_search(input, wynik, wzor)) //oczyt danych jesli pasuja
    {
        ss >> trash;
        for (int i = 0; i < ROZMIAR; i++)
            ss >> W[i];
    }
    else //jesli nie to blad
    {
        cerr << "[!] Incorrect input in Wektor" << endl;
        exit(1); //albo strm.setstate(ios::failbit);
    }

    return strm;
}

/*Specjalizacja wczytywania dla LZ*/

template <>
istream & operator>>(istream &strm, Wektor<LZ, _ROZMIAR> &W)
{
    char trash;

    strm >> trash;

    for(int i = 0; i < _ROZMIAR; i++)
    {
        strm >> W[i];
        if( !strm.good() )
        {
            cerr << "[!]Input error" << endl;
            exit(1);
        }
    }

    strm >> trash;

    return strm;
}