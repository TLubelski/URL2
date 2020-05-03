#include "common.hh"
#include "LZespolona.hh"
#include "Wektor.cpp"

/*Wymuszenie kompilacji dla double*/
template class Wektor<double, _ROZMIAR>;
template Wektor<double, _ROZMIAR> operator*(double l1, const Wektor<double, _ROZMIAR> W2);
template std::ostream &operator<<(std::ostream &strm, const Wektor<double, _ROZMIAR> &W);
template std::istream &operator>>(std::istream &strm, Wektor<double, _ROZMIAR> &W);

/*Wymuszenie kompilacji dla LZ*/
template class Wektor<LZ, _ROZMIAR>;
template Wektor<LZ, _ROZMIAR> operator*(LZ l1, const Wektor<LZ, _ROZMIAR> W2);
template std::ostream &operator<<(std::ostream &strm, const Wektor<LZ, _ROZMIAR> &W);
template std::istream &operator>>(std::istream &strm, Wektor<LZ, _ROZMIAR> &W);