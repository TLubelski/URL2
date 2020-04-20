#ifndef LZESPOLONA_HH
#define LZESPOLONA_HH

#include <iostream>



struct  LZespolona {
  double   re;    //czesc rzeczywista
  double   im;    //czesc urojona
};


/*Basic*/
LZespolona utworzLZ(double _re, double _im); 


/*Op strumieniowe*/
std::istream & operator >> (std::istream & strm, LZespolona & z);
std::ostream & operator << (std::ostream & strm, const LZespolona & z);


/*Op Wlasne*/
double modul(LZespolona z);
LZespolona sprzez(LZespolona z);


/*Op Arytmetyczne*/
LZespolona  operator + (LZespolona  z1,  LZespolona  z2);
LZespolona  operator - (LZespolona  z1,  LZespolona  z2);
LZespolona  operator * (LZespolona  z1,  LZespolona  z2);
LZespolona  operator / (LZespolona  z1,  double  dzielnik);
LZespolona  operator / (LZespolona  z1,  LZespolona  z2);


/*Op Logiczne*/
bool operator == (LZespolona  z1,  LZespolona  z2);
bool operator != (LZespolona  z1,  LZespolona  z2);


#endif
