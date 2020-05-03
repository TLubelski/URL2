#include "common.hh"
#include "MacierzKw.cpp"

/*Wymuszenie kompilacji dla double*/
template class MacierzKw<double, _ROZMIAR>;
template MacierzKw<double, _ROZMIAR> operator*(double l1, const MacierzKw<double, _ROZMIAR> M2);
template std::ostream &operator<<(std::ostream &strm, const MacierzKw<double, _ROZMIAR> &M);
template std::istream &operator>>(std::istream &strm, MacierzKw<double, _ROZMIAR> &M);

/*Wymuszenie kompilacji dla LZ*/
template class MacierzKw<LZ, _ROZMIAR>;
template MacierzKw<LZ, _ROZMIAR> operator*(LZ l1, const MacierzKw<LZ, _ROZMIAR> M2);
template std::ostream &operator<<(std::ostream &strm, const MacierzKw<LZ, _ROZMIAR> &M);
template std::istream &operator>>(std::istream &strm, MacierzKw<LZ, _ROZMIAR> &M);
