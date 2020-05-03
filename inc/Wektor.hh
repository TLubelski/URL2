#ifndef WEKTOR_HH
#define WEKTOR_HH

#include "common.hh"

#include <iostream>


/*Szablon opisujacy klase wektor*/
template <typename TYP, int ROZMIAR>
class Wektor
{
private:
    TYP tab[ROZMIAR];

public:
    /*KONSTRUKTORY*/
    Wektor();
    Wektor(TYP *tab);

    /*OPERATORY*/
    const TYP &operator[](int index) const;
    TYP &operator[](int index);
    
    bool operator==(const Wektor &W2) const;
    bool operator!=(const Wektor &W2) const;

    Wektor operator+(const Wektor &W2) const;
    const Wektor & operator+=(const Wektor &W2);

    Wektor operator-(const Wektor &W2) const;
    const Wektor & operator-=(const Wektor &W2);

    TYP operator*(const Wektor &W2) const; //iloczyn skalarny

    Wektor operator/(TYP dzielnik) const;

    /*API*/
    double dlugosc() const;
};


/*OPERATORY ZEWNETRZNE*/
template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR> operator*(TYP l1, const Wektor<TYP, ROZMIAR> W2); //mnozenie przez liczbe

template <typename TYP, int ROZMIAR>
std::ostream &operator<<(std::ostream &strm, const Wektor<TYP, ROZMIAR> &W);

template <typename TYP, int ROZMIAR>
std::istream &operator>>(std::istream &strm, Wektor<TYP, ROZMIAR> &W);


#endif