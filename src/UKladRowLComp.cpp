#include "common.hh"
#include "UklRowL.hh"

/*Wymuszenie kompilacji dla double*/
template class UklRowL<double, _ROZMIAR>;
template std::ostream &operator<<(std::ostream &strm, const UklRowL<double, _ROZMIAR> &Uklad);
template std::istream &operator>>(std::istream &strm, UklRowL<double, _ROZMIAR> &Uklad);

/*Wymuszenie kompilacji dla LZ*/
template class UklRowL<LZ, _ROZMIAR>;
template std::ostream &operator<<(std::ostream &strm, const UklRowL<LZ, _ROZMIAR> &Uklad);
template std::istream &operator>>(std::istream &strm, UklRowL<LZ, _ROZMIAR> &Uklad);