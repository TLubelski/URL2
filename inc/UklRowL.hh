#ifndef UKL_ROW_L_HH
#define UKL_ROW_L_HH

#include "Wektor.hh"
#include "MacierzKw.hh"

#include <iostream>

template<typename TYP, int ROZMIAR>
class UklRowL
{
private:
    MacierzKw<TYP, ROZMIAR> A;
    Wektor<TYP, ROZMIAR> b;

public:
    UklRowL(){}
    UklRowL(MacierzKw<TYP, ROZMIAR> _A, Wektor<TYP, ROZMIAR> _b) : A(_A), b(_b){};

    const Wektor<TYP, ROZMIAR> &get_wektor_wolny() const;
    void set_wektor_wolny(const Wektor<TYP, ROZMIAR> &W_n);

    const MacierzKw<TYP, ROZMIAR> &get_macierz() const;
    void set_macierz(const MacierzKw<TYP, ROZMIAR> &M_n);

    Wektor<TYP, ROZMIAR> oblicz() const;

    Wektor<TYP, ROZMIAR> wekt_bledu() const;
};

template <typename TYP, int ROZMIAR>
std::ostream & operator<<(std::ostream &strm, const UklRowL<TYP, ROZMIAR> &Uklad);

template <typename TYP, int ROZMIAR>
std::istream & operator>>(std::istream &strm, UklRowL<TYP, ROZMIAR> &Uklad);

#endif