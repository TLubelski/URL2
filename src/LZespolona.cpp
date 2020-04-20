#include "LZespolona.hh"
#include <cmath>
#include <regex>
#include <sstream>

/* Basic*/

LZespolona utworzLZ(double _re, double _im)
{
  LZespolona temp;
  temp.re = _re;
  temp.im = _im;
  return temp;
}

/*Op strumieniowe*/

std::istream &operator>>(std::istream &strm, LZespolona &z)
{
  using namespace std;

  stringstream ss;
  string input;
  smatch wynik;
  char x; //smietnik

  regex normal("\\(-?\\d+.?\\d*(\\+|-)\\d+.?\\d*i\\)");
  regex im_only("\\(\\d+.?\\d*i\\)");
  regex im_only_i("\\(i\\)");
  regex im_only_mi("\\(-i\\)");
  regex re_only("\\(-?\\d+.?\\d*\\)");

  strm >> input;
  ss << input;

  if (regex_search(input, wynik, normal))
  {
    ss >> x >> z.re >> z.im >> x >> x;
  }
  else if (regex_search(input, wynik, im_only))
  {
    z.re = 0;
    ss >> x >> z.im >> x >> x;
  }
  else if (regex_search(input, wynik, im_only_i))
  {
    z.re = 0;
    z.im = 1;
    ss >> x >> x >> x;
  }
  else if (regex_search(input, wynik, im_only_mi))
  {
    z.re = 0;
    z.im = -1;
    ss >> x >> x >> x >> x;
  }
  else if (regex_search(input, wynik, re_only))
  {
    ss >> x >> z.re >> x;
    z.im = 0;
  }
  else
  {
    strm.setstate(ios::failbit);
  }

  return strm;
}

std::ostream &operator<<(std::ostream &strm, const LZespolona &z)
{
  strm << "(" << z.re << std::showpos << z.im << std::noshowpos << "i)";
  return strm;
}

/*Op Wlasne*/

double modul(LZespolona z)
{
  return sqrt(z.re * z.re + z.im * z.im);
}

LZespolona sprzez(LZespolona z)
{
  z.im *= (-1);
  return z;
}

/*Op Arytmetyczne*/

LZespolona operator+(LZespolona z1, LZespolona z2)
{
  LZespolona Wynik;

  Wynik.re = z1.re + z2.re;
  Wynik.im = z1.im + z2.im;
  return Wynik;
}

LZespolona operator-(LZespolona z1, LZespolona z2)
{
  LZespolona Wynik;

  Wynik.re = z1.re - z2.re;
  Wynik.im = z1.im - z2.im;
  return Wynik;
}

LZespolona operator*(LZespolona z1, LZespolona z2)
{
  LZespolona Wynik;

  Wynik.re = z1.re * z2.re - z1.im * z2.im;
  Wynik.im = z1.re * z2.im + z1.im * z2.re;
  return Wynik;
}

LZespolona operator/(LZespolona z1, double dzielnik)
{
  if (dzielnik == 0)
  {
    std::cerr << "[!]Blad: Wykryto dzielenie przez 0" << std::endl;
    exit(1);
  }

  LZespolona Wynik;
  Wynik.re = z1.re / dzielnik;
  Wynik.im = z1.im / dzielnik;
  return Wynik;
}

LZespolona operator/(LZespolona z1, LZespolona z2)
{
  double dzielnik = modul(z2) * modul(z2);

  return (z1 * sprzez(z2)) / dzielnik;
}

/*Op Logiczne*/

bool operator==(LZespolona z1, LZespolona z2)
{
  if (z1.re == z1.re && z1.im == z2.im)
    return true;
  else
    return false;
}

bool operator!=(LZespolona z1, LZespolona z2)
{
  return !(z1 == z2);
}
