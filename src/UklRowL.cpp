#include "UklRowL.hh"

using namespace std;

template <typename TYP, int ROZMIAR>
const Wektor<TYP, ROZMIAR> &UklRowL<TYP, ROZMIAR>::get_wektor_wolny() const
{
    return b;
}

template <typename TYP, int ROZMIAR>
void UklRowL<TYP, ROZMIAR>::set_wektor_wolny(const Wektor<TYP, ROZMIAR> &W_n)
{
    b = W_n;
}

template <typename TYP, int ROZMIAR>
const MacierzKw<TYP, ROZMIAR> &UklRowL<TYP, ROZMIAR>::get_macierz() const
{
    return A;
}

template <typename TYP, int ROZMIAR>
void UklRowL<TYP, ROZMIAR>::set_macierz(const MacierzKw<TYP, ROZMIAR> &M_n)
{
    A = M_n;
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR> UklRowL<TYP, ROZMIAR>::oblicz() const
{
    return ( A.odwrotnosc() * b );
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR> UklRowL<TYP, ROZMIAR>::wekt_bledu() const
{
    return A * oblicz() - b;
}

template <typename TYP, int ROZMIAR>
ostream & operator<<(ostream &strm, const UklRowL<TYP, ROZMIAR> &Uklad)
{
    MacierzKw<TYP, ROZMIAR> macierz = Uklad.get_macierz();
    Wektor<TYP, ROZMIAR> wolny = Uklad.get_wektor_wolny();

    for(int i = 0; i < ROZMIAR; i++)
    {
        strm << macierz[i] << "  " << "|x_" << i+1 << "|";

        if(i == 1)
            strm << " = ";
        else
            strm << "   ";

        strm << "|" << wolny[i] << "|" << endl;
    }
    return strm;
}

template <typename TYP, int ROZMIAR>
istream & operator>>(istream &strm, UklRowL<TYP, ROZMIAR> &Uklad)
{
    MacierzKw<TYP, ROZMIAR> temp_m;
    Wektor<TYP, ROZMIAR> temp_w;

    strm >> temp_m;
    temp_m = temp_m.transpozycja(); //powrot do postacie nietransponowanej
    Uklad.set_macierz( temp_m );
    
    strm >> temp_w;
    Uklad.set_wektor_wolny(temp_w);

    return strm;
}