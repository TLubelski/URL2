#include "MacierzKw.hh"

#include <iostream>
#include <cmath>

using namespace std;

/***KONSTRUKTORY***/
template <typename TYP, int ROZMIAR>
MacierzKw<TYP, ROZMIAR>::MacierzKw(Wektor<TYP, ROZMIAR> *W)
{
    for (int i = 0; i < ROZMIAR; i++)
        this->tab[i] = W[i];
}


/***OPERATORY***/

template <typename TYP, int ROZMIAR>
const Wektor<TYP, ROZMIAR> & MacierzKw<TYP, ROZMIAR>::operator[](int index) const
{
    if (index < 0 || index >= ROZMIAR)
    {
        cerr << "[!] Index out of range in MacierzKw" << endl;
        exit(1);
    }
    return tab[index];
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR> & MacierzKw<TYP, ROZMIAR>::operator[](int index)
{
    if (index < 0 || index >= ROZMIAR)
    {
        cerr << "[!] Index out of range in MacierzKw" << endl;
        exit(1);
    }
    return tab[index];
}

template <typename TYP, int ROZMIAR>
bool MacierzKw<TYP, ROZMIAR>::operator==(const MacierzKw &M2) const
{
    bool wynik = true;
    for (int i = 0; i < ROZMIAR; i++)
    {
        if (tab[i] != M2.tab[i])
            wynik = false;
    }
    return wynik;
}

template <typename TYP, int ROZMIAR>
bool MacierzKw<TYP, ROZMIAR>::operator!=(const MacierzKw &M2) const
{
    return !(*this == M2);
}

template <typename TYP, int ROZMIAR>
MacierzKw<TYP, ROZMIAR> MacierzKw<TYP, ROZMIAR>::operator+(const MacierzKw &M2) const
{
    MacierzKw temp;
    for (int i = 0; i < ROZMIAR; i++)
        temp.tab[i] = tab[i] + M2.tab[i];
    return temp;
}

template <typename TYP, int ROZMIAR>
const MacierzKw<TYP, ROZMIAR> &MacierzKw<TYP, ROZMIAR>::operator+=(const MacierzKw &M2)
{
    *this = *this + M2;
    return *this;
}

template <typename TYP, int ROZMIAR>
MacierzKw<TYP, ROZMIAR> MacierzKw<TYP, ROZMIAR>::operator-(const MacierzKw &M2) const
{
    MacierzKw temp;
    for (int i = 0; i < ROZMIAR; i++)
        temp.tab[i] = tab[i] - M2.tab[i];
    return temp;
}

template <typename TYP, int ROZMIAR>
const MacierzKw<TYP, ROZMIAR> &MacierzKw<TYP, ROZMIAR>::operator-=(const MacierzKw &M2)
{
    *this = *this - M2;
    return *this;
}

template <typename TYP, int ROZMIAR>
MacierzKw<TYP, ROZMIAR> MacierzKw<TYP, ROZMIAR>::operator*(const MacierzKw &M2) const
{
    MacierzKw temp;
    for (int i = 0; i < ROZMIAR; i++)
    {
        for (int j = 0; j < ROZMIAR; j++)
        {
            temp[i][j] = 0;
            for (int k = 0; k < ROZMIAR; k++) //mnozenie wiersz x kolumny
                temp[i][j] += tab[i][k] * M2[k][j];
        }
    }
    return temp;
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR> MacierzKw<TYP, ROZMIAR>::operator*(const Wektor<TYP, ROZMIAR> &W2) const
{
    Wektor<TYP, ROZMIAR> temp(0,0,0);
    for (int i = 0; i < ROZMIAR; i++)
    {
        for (int j = 0; j < ROZMIAR; j++)
        {
            temp[i] += tab[i][j] * W2[j]; 
        }
    }
    return temp;
}

/*****API******/

template <typename TYP, int ROZMIAR>
void MacierzKw<TYP, ROZMIAR>::utworzI()
{
    for (int i = 0; i < ROZMIAR; i++)
    {
        for (int j = 0; j < ROZMIAR; j++)
        {
            tab[i][j] = (i == j) ? 1 : 0;
        }
    }
}

template <typename TYP, int ROZMIAR>
MacierzKw<TYP, ROZMIAR> MacierzKw<TYP, ROZMIAR>::schodkowa() const
{
    MacierzKw temp = *this;
    double mnoznik;
    for (int i = 0; i < ROZMIAR - 1; i++)
    {
        for (int j = i + 1; j < ROZMIAR; j++)
        {
            if( cmp(temp[i][i], 0) )
            {
                cerr << "[!]Dzielenie przez 0" << endl;
                exit(1);
            }
            mnoznik = -temp[j][i] / temp[i][i]; //obliczanie mnoznika  wiersza
            temp[j] += mnoznik * temp[i]; //dodwawanie pomnozonego wiersza by uzyskac 0
        }
    }
    return temp;

}

template <typename TYP, int ROZMIAR>
MacierzKw<TYP, ROZMIAR> MacierzKw<TYP, ROZMIAR>::transpozycja() const
{
    MacierzKw temp;
    for (int i = 0; i < ROZMIAR; i++)
    {
        for (int j = 0; j < ROZMIAR; j++)
        {
            temp[i][j] = tab[j][i]; //zamina wierszy z kolumnami
        }
    }
    return temp;
}

template <typename TYP, int ROZMIAR>
double MacierzKw<TYP, ROZMIAR>::wyznacznik(Wyz metoda) const
{
    double det = 0;
    
    if( ROZMIAR == 2) //macierz 2x2 na krzyz
    {
        det = tab[0][0] * tab[1][1] - tab[0][1] * tab[1][0];  
    }
    else if(ROZMIAR >= 3) // macierz 3x3 i wieksza
    {
        switch ( metoda )
        {
        case Bareiss:
            det = this->w_bareiss();
            break;
        
        case Gauss:
            det = this->w_gauss();
            break;

        case Sarruss:
            if(ROZMIAR != 3)
            {
                cerr << "[!] Incorrect method in Wyznacznik" << endl;
                exit(1);
            }
            det = this->w_sarruss();
            break;
        }
    }

    if (cmp(det, 0) ) //zabezpieczenie przed wynikiem -0
        det = 0;

    return det;
}

template <typename TYP, int ROZMIAR>
MacierzKw<TYP, ROZMIAR> MacierzKw<TYP, ROZMIAR>::odwrotnosc() const
{
    MacierzKw temp = *this;
    MacierzKw dolaczona;
    dolaczona.utworzI();
    double mnoznik;

    if( cmp(temp.wyznacznik(), 0) )
    {
        cerr << "[!]Wyznacznik 0, macierz nieodwracalna" << endl;
        exit(1);
    }

    //do schodkowej
    for (int i = 0; i < ROZMIAR - 1; i++)
    {
        for (int j = i + 1; j < ROZMIAR; j++)
        {
            if ( cmp(temp[i][i], 0) )
            {
                cerr << "[!]Dzielenie przez 0" << endl;
                exit(1);
            }
            mnoznik = -temp[j][i] / temp[i][i]; //obliczanie mnoznika  wiersza
            temp[j] += mnoznik * temp[i];       //dodwawanie pomnozonego wiersza by uzyskac 0
            dolaczona[j] += mnoznik * dolaczona[i];
        }
    }

    //do diagonalnej
    for (int i = ROZMIAR - 1; i > 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if ( cmp(temp[i][i], 0) )
            {
                cerr << "[!]Dzielenie przez 0" << endl;
                exit(1);
            }
            mnoznik = -temp[j][i] / temp[i][i]; //obliczanie mnoznika  wiersza
            temp[j] += mnoznik * temp[i];       //dodwawanie pomnozonego wiersza by uzyskac 0
            dolaczona[j] += mnoznik * dolaczona[i];
        }
    }

    //do jednostkowej
    for(int i = 0; i < ROZMIAR; i++)
    {
        dolaczona[i] = (1.0 / temp[i][i]) * dolaczona[i];
        temp[i] = (1.0 / temp[i][i]) * temp[i];
    }

    return dolaczona;
}


/***METODY WEWNETRZNE***/

template <typename TYP, int ROZMIAR>
double MacierzKw<TYP, ROZMIAR>::w_gauss() const
{
    double det = 1;
    MacierzKw temp = this->schodkowa();

    for (int i = 0; i < ROZMIAR; i++) //mnozenie po glownej przekatnej
        det *= temp[i][i];

    return det;
}

template <typename TYP, int ROZMIAR>
double MacierzKw<TYP, ROZMIAR>::w_bareiss() const
{
    MacierzKw temp = *this;

    for (int i = 0; i < ROZMIAR - 1; i++)
        for (int j = i + 1; j < ROZMIAR; j++)
            for (int k = i + 1; k < ROZMIAR; k++)
            {
                temp[j][k] = (temp[j][k] * temp[i][i] - temp[j][i] * temp[i][k]);
                if (i)
                {
                    if( cmp(temp[i-1][i-1], 0) )
                    {
                        cerr << "[!]Dzielenie przez 0" << endl;
                        exit(1);
                    }
                    temp[j][k] /= temp[i - 1][i - 1];
                }

            }

    return temp[ROZMIAR - 1][ROZMIAR - 1];
}

template <typename TYP, int ROZMIAR>
double MacierzKw<TYP, ROZMIAR>::w_sarruss() const
{
    double det;
    det = (tab[0][0] * tab[1][1] * tab[2][2] + tab[0][1] * tab[1][2] * tab[2][0] + tab[0][2] * tab[1][0] * tab[2][1]);
    det -= (tab[0][2] * tab[1][1] * tab[2][0] + tab[0][0] * tab[1][2] * tab[2][1] + tab[0][1] * tab[1][0] * tab[2][2]);
    return det;
}

/***OPERATORY ZEWNETRZNE***/

template <typename TYP, int ROZMIAR>
MacierzKw<TYP, ROZMIAR> operator*(TYP l1, const MacierzKw<TYP, ROZMIAR> M2) //mnozenie przez liczbe
{
    MacierzKw temp<TYP, ROZMIAR>;
    for (int i = 0; i < ROZMIAR; i++)
        temp[i] = l1 * M2[i];
    return temp;
}

template <typename TYP, int ROZMIAR>
std::ostream &operator<<(std::ostream &strm, const MacierzKw<TYP, ROZMIAR> &M)
{
    for(int i =0; i < ROZMIAR; i++)
    {
        strm << M[i] << endl;
    }
    return strm;
}

template <typename TYP, int ROZMIAR>
std::istream &operator>>(std::istream &strm, MacierzKw<TYP, ROZMIAR> &M)
{
    for (int i = 0; i < ROZMIAR; i++)
    {
        strm >> M[i];
    }
    return strm;
}