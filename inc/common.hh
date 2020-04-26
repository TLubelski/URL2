#ifndef COMMON_HH
#define COMMON_HH

#include "LZespolona.hh"
#include <cmath>

#define _ROZMIAR 5

const double eps = 0.000001; //epsilon

/*Dokladne porownania*/

bool cmp(double l1, double l2); // double z double

bool cmp(const LZ &z1, const LZ &z2); // LZ z LZ

bool cmp(const LZ &z1, double l1); //LZ z dobule

bool cmp(double l1, const LZ &z2); //double z LZ

#endif