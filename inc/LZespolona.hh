#ifndef LZESPOLONA_HH
#define LZESPOLONA_HH

#include <iostream>

class LZ{
private:
    double re;    //czesc rzeczywista
    double im;    //czesc urojona

public:
    /*Konstruktory*/
    LZ() : re(0), im(0){}
    LZ(double _re, double _im) : re(_re), im(_im){}

    const LZ & operator=(double l){ re = l; im = 0; return *this; } 
    //const LZ & operator=(int l){ re = l; im = 0; return *this; }

    /*SET/GET*/
    void setRe(double re) { this->re = re; }
    double getRe() const { return re; }

    void setIm(double im) {this-> im = im; }
    double getIm() const { return im; }

    /*Metody zewnetrzne*/
    double modul() const;
    LZ sprzez() const ;

    /*Op Arytmetyczne*/
    LZ operator+(const LZ &z2) const;
    const LZ & operator+=(const LZ &z2);
    
    LZ operator-(const LZ &z2) const;
    const LZ & operator-=(const LZ &z2);
    
    LZ operator*(const LZ &z2) const;
    const LZ & operator*=(const LZ &z2);

    LZ operator*(double mnoznik) const;

    LZ operator/(double dzielnik) const;
    const LZ & operator/=(double dzielnik);

    LZ operator/(const LZ &z2) const;
    const LZ & operator/=(const LZ &z2);
    
    /*Op Logiczne*/
    bool operator==(const LZ &z2) const;
    bool operator!=(const LZ &z2) const;
};

LZ operator*(double mnoznik,const LZ &z);
LZ operator/(double dzielna, const LZ &z);

/*Op strumieniowe*/
std::istream &operator>>(std::istream &strm, LZ &z);
std::ostream &operator<<(std::ostream &strm, const LZ &z);

#endif
