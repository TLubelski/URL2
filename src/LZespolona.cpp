#include "LZespolona.hh"
#include "common.hh"

#include <regex>
#include <sstream>


/*Metody zewnetrzne*/

double LZ::modul() const
{
    return sqrt(re * re + im * im);
}

LZ LZ::sprzez() const
{
    LZ tmp = *this;
    tmp.im = -tmp.im;
    return tmp;
}

/*Op Arytmetyczne*/

LZ LZ::operator+(const LZ &z2) const
{
    LZ Wynik;

    Wynik.re = re + z2.re;
    Wynik.im = im + z2.im;
    return Wynik;
}

const LZ & LZ::operator+=(const LZ &z2)
{
    *this = *this + z2;
    return *this;
}

LZ LZ::operator-(const LZ &z2) const
{
    LZ Wynik;

    Wynik.re = re - z2.re;
    Wynik.im = im - z2.im;
    return Wynik;
}

const LZ & LZ::operator-=(const LZ &z2)
{
    *this = *this - z2;
    return *this;
}

LZ LZ::operator*(const LZ &z2) const
{
    LZ Wynik;

    Wynik.re = re * z2.re - im * z2.im;
    Wynik.im = re * z2.im + im * z2.re;
    return Wynik;
}

const LZ & LZ::operator*=(const LZ &z2)
{
    *this = *this * z2;
    return *this;
}

LZ LZ::operator*(double mnoznik) const
{
    return LZ(re * mnoznik, im * mnoznik);
}

LZ LZ::operator/(double dzielnik) const
{
    if ( cmp(dzielnik, 0) )
    {
        std::cerr << "[!]Dzielenie przez 0 w LZ" << std::endl;
        exit(1);
    }

    LZ Wynik;
    Wynik.re = re / dzielnik;
    Wynik.im = im / dzielnik;
    return Wynik;
}

const LZ & LZ::operator/=(double dzielnik)
{
    *this = *this / dzielnik;
    return *this;
}

LZ LZ::operator/(const LZ &z2) const
{
    double dzielnik = z2.modul() * z2.modul();

    return ( *this * z2.sprzez() ) / dzielnik;
}

const LZ & LZ::operator/=(const LZ &z2)
{
    *this = *this / z2;
    return *this;
}

/*Op Logiczne*/

bool LZ::operator==(const LZ &z2) const
{
    if ( cmp(re, z2.re) && cmp(im, z2.im) )
        return true;
    else
        return false;
}

bool LZ::operator!=(const LZ &z2) const
{
    return !(*this == z2);
}

LZ operator*(double mnoznik, const LZ &z)
{
    return LZ(z.getRe() * mnoznik, z.getIm() * mnoznik);
}

LZ operator/(double dzielna, const LZ &z)
{
    return LZ(dzielna / z.getRe(), dzielna / z.getIm());
}

/*Op strumieniowe*/
std::istream &operator>>(std::istream &strm, LZ &z)
{
    using namespace std;

    stringstream ss;
    string input;
    smatch wynik;
    char x; //smietnik
    double tmp;

    regex normal("\\(-?\\d+.?\\d*(\\+|-)\\d+.?\\d*i\\)");
    regex im_only("\\(\\d+.?\\d*i\\)");
    regex im_only_i("\\(i\\)");
    regex im_only_mi("\\(-i\\)");
    regex re_only("\\(-?\\d+.?\\d*\\)");

    strm >> input;
    ss << input;

    if (regex_search(input, wynik, normal))
    {
        ss >> x >> tmp; 
        z.setRe(tmp);
        ss >> tmp >> x >> x;
        z.setIm(tmp);
    }
    else if (regex_search(input, wynik, im_only))
    {
        z.setRe(0);
        ss >> x >> tmp >> x >> x;
        z.setIm(tmp);
    }
    else if (regex_search(input, wynik, im_only_i))
    {
        z.setRe(0);
        z.setIm(1);
        ss >> x >> x >> x;
    }
    else if (regex_search(input, wynik, im_only_mi))
    {
        z.setRe(0);
        z.setIm(-1);
        ss >> x >> x >> x >> x;
    }
    else if (regex_search(input, wynik, re_only))
    {
        ss >> x >> tmp >> x;
        z.setRe(tmp);
        z.setIm(0);
    }
    else
    {
        strm.setstate(ios::failbit);
    }

    return strm;
}

std::ostream &operator<<(std::ostream &strm, const LZ &z)
{
    strm << "(" << z.getRe() << std::showpos << z.getIm() << std::noshowpos << "i)";
    return strm;
}