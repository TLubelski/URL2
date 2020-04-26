#include "common.hh"


/*Dokladne porownania*/

bool cmp(double l1, double l2) // double z double
{
    return (fabs(l1 - l2) < eps) ? true : false;
}

bool cmp(const LZ &z1, const LZ &z2) // LZ z LZ
{
    if( cmp(z1.getRe(), z2.getRe()) && cmp(z1.getIm(), z2.getIm()) )
        return true;
    else
        return false;
}

bool cmp(const LZ &z1, double l1) //LZ z dobule
{
    if ( cmp(z1.getRe(), l1) && cmp(z1.getIm(), 0) )
        return true;
    else
        return false;
}

bool cmp(double l1, const LZ &z1) //double z LZ
{
    if ( cmp(z1.getRe(), l1) && cmp(z1.getIm(), 0) )
        return true;
    else
        return false;
}