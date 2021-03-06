#ifndef MACIERZKW_HH
#define MACIERZKW_HH

#include "Wektor.hh"

enum Wyz{Gauss, Sarruss, Bareiss}; //wybor metody liczenia wyznacznika


/*Szablon opisujacy klase macierz kwadratowa*/
template<typename TYP, int ROZMIAR>
class MacierzKw
{
private:
    Wektor<TYP, ROZMIAR> tab[ROZMIAR]; //kazdemu wierszowi odpowiada wektor

    /*METODY WEWNETRZNE*/
    TYP w_gauss() const; //pojawil sie problem z dokladnoscia double
    TYP w_bareiss() const;
    TYP w_sarruss() const;
    void zamien_wiersze(int i1, int i2);

public:
    /*KONSTRUKTORY*/
    MacierzKw(){}
    MacierzKw(Wektor<TYP, ROZMIAR> *W); //przyjmuje tablice wektorow
    
    /*OPERATORY*/
    const Wektor<TYP, ROZMIAR> & operator[](int index) const;
    Wektor<TYP, ROZMIAR> & operator[](int index);

    bool operator==(const MacierzKw &M2) const;
    bool operator!=(const MacierzKw &M2) const;

    MacierzKw operator+(const MacierzKw &M2) const;
    const MacierzKw & operator+=(const MacierzKw &M2);

    MacierzKw operator-(const MacierzKw &M2) const;
    const MacierzKw & operator-=(const MacierzKw &M2);

    MacierzKw operator*(const MacierzKw &M2) const; //mnozenie dwoch macierzy
    
    Wektor<TYP, ROZMIAR> operator*(const Wektor<TYP, ROZMIAR> &W2) const; //mnozenie przez wektor

    /*API*/
    void utworzI(); //tworzy macierz jednostkowa

    MacierzKw schodkowa() const; //zwraca macierz schodkowa

    MacierzKw transpozycja() const; 

    TYP wyznacznik(Wyz metoda = Bareiss) const;

    MacierzKw odwrotnosc() const; //WIP
};

/*OPERATORY ZEWNETRZNE*/

template <typename TYP, int ROZMIAR>
MacierzKw<TYP,ROZMIAR> operator*(TYP l1, const MacierzKw<TYP,ROZMIAR> M2); //mnozenie macierzy przez liczbe

template <typename TYP, int ROZMIAR>
std::ostream &operator<<(std::ostream &strm, const MacierzKw<TYP,ROZMIAR> &M); //wyswietlanie wierszami

template <typename TYP, int ROZMIAR>
std::istream &operator>>(std::istream &strm, MacierzKw<TYP,ROZMIAR> &M); //wczytywanie wierszami

#endif