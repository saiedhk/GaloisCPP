/**********************************************************************

       Project: C++ Library for General Galois Field Arithmetic

   Language: C++ 2007	   
   Author: Saied H. Khayat
   Date:   February 2013
   Project URL: https://github.com/saiedhk/galoiscpp
   
   Copyright Notice: Free use of this library is permitted under the
   guidelines and in accordance with the MIT License (MIT).
   http://opensource.org/licenses/MIT

**********************************************************************/

/*
   Modular arithmetic operations
*/

#include <iostream>
using namespace std;

#include "typedefs.h"

#ifndef MODULAR_ARITH_H
#define MODULAR_ARITH_H

namespace shk_galoiscpp
{

/**
   Implements the Extended Euclid Algorithm.

   It computes the greatest common divisor d of two positive integers a and b
   and determine two integers x and y such that d = ax + by.

   (See Chapter 2, Algorithm 2.107 in Handbook of Applied Cryptography,
   by Menezes, van Oorschot, Vanstone, CRC Press, 1996.)

   @param a input integer (a > 0)
   @param b input integer (b > 0)
   @param x output integer
   @param y output integer
   @param d output integer (greatest common divisor of a and b)
*/
void extendedEuclid(Fint a, Fint b, Fint& x, Fint& y, Fint& d);


//------------------------------------------------
// modular arithmetic functions
//------------------------------------------------

/**
   Adds two integers modulo m
   @param a input integer
   @param b input integer
   @param mod input integer (modulus)
   @returns sum modulo mod
*/
inline Fint addModular(Fint a, Fint b, Fint mod)
{
   return (a + b) % mod;
}


/**
   Subtracts two integers modulo m
   @param a input integer
   @param b input integer
   @param mod input integer (modulus)
   @returns difference modulo mod
*/
inline Fint subtractModular(Fint a, Fint b, Fint mod)
{
   return (a + (mod - b)) % mod;
}

/**
   Multiplies two integers modulo m
   @param a input integer
   @param b input integer
   @param mod input integer (modulus)
   @returns product modulo mod
*/
inline Fint multiplyModular(Fint a, Fint b, Fint mod)
{
   return (a * b) % mod;
}


/**
   Determines the multiplicative inverse of an integer modulo mod
   @param a input integer (a>0)
   @param mod input integer (modulus, mod>0)
   @returns b the inverse of a such that a * b = 1 modulo mod
   @throws ErrorNoInverse if mod is not prime relative to a
*/
inline Fint inverseModular(Fint a, Fint mod)
{
   Fint d,x,y;

   // compute modular multiplicative inverse of b (exists if d=1)
   extendedEuclid(a,mod,x,y,d);

   if (d != 1) // if a and m are not relatively prime, there is no inverse.
   {
      throw ErrorNoInverse;
   }

   return ( (x>0) ? x : (mod + x) );
}


/**
   Divides two integers modulo mod
   @param a input integer (dividend)
   @param b input integer (divisor)
   @param mod input integer (modulus)
   @returns q quotient such that a = q * b modulo mod
   @throws ErrorNoInverse if mod is not prime relative to a, or ErrorDivideByZero if b=0
*/
inline Fint divideModular(Fint a, Fint b, Fint mod)
{
   if (b==0)
   {
      throw ErrorDivideByZero;
   }
   return (a * inverseModular(b,mod)) % mod;
}


} // namespace shk_galoiscpp

#endif