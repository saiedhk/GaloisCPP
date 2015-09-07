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
   Polynomial arithmetic over a prime field
*/

#include <cassert>
#include "modular_arith.h"

#ifndef POLYNOMIAL_ARITH_H
#define POLYNOMIAL_ARITH_H

namespace shk_galoiscpp
{


/**
   Implements addition of two polynomials over a finite ring

   It adds polynomial A to polynomial B.  (i.e., S = A + B)

   @param A input, addend polynomial (an array of Fint elements)
   @param Alen input length of array A (Alen>0)
   @param B input, addend polynomial (an array of Fint elements)
   @param Blen input length of array B (Blen>0)
   @param S output, sum polynomial (an array of Fint elements)
   @param Slen input integer (Slen>=max(Alen,Blen))
   @param modulus input, a positive integer
   @throws ErrorInvalidArraySize
*/
void polynomialAdd(const Fint A[], Int Alen,
                   const Fint B[], Int Blen,
                         Fint S[], Int Slen,  // S = A + B
                         Fint modulus);




/**
   Implements subtraction of two polynomials over a finite ring.

   It subtracts polynomial B from polynomial A. (i.e., D = A - B))

   @param A input, minuend polynomial (an array of Fint elements)
   @param Alen input length of array A (Alen>0)
   @param B input, subtrahend polynomial (an array of Fint elements)
   @param Blen input length of array B (Blen>0)
   @param D output, difference polynomial (an array of Fint elements)
   @param Dlen input integer (Dlen>=max(Alen,Blen))
   @param modulus input, a positive integer
   @throws ErrorInvalidArraySize
*/
void polynomialSubtract(const Fint A[], Int Alen,
                        const Fint B[], Int Blen,
                              Fint D[], Int Dlen,  // D = A - B
                              Fint modulus);




/**
   Implements multiplication of two polynomials.

   It multiplies polynomial A by polynomial B.

   @param A input, multiplicand polynomial (an array of Fint elements)
   @param Alen input length of array A (Alen>0)
   @param B input, multiplier polynomial (an array of Fint elements)
   @param Blen input length of array B (Blen>0)
   @param P output, product polynomial (an array of Fint elements)
   @param Plen input integer (Plen>=Alen+Blen-1)
   @param modulus input, a positive integer
   @throws ErrorInvalidArraySize
*/
void polynomialMultiply(const Fint A[], Int Alen,
                        const Fint B[], Int Blen,
                              Fint P[], Int Plen,
                              Fint modulus);



/**
   Implements long division of two polynomials over a prime field

   It divides polynomial A by polynomial B and determines the resulting
   quotient Q and remainder R (such that A = BQ + R).

   @param A input, dividend polynomial (an array of Fint elements)
   @param Alen input integer (length of array A) (Alen>0)
   @param B input, divisor polynomial (an array of Fint elements)
   @param Blen input integer (length of array B) (Blen>0)
   @param Q output, quotient polynomial (an array of Fint elements)
   @param Qlen input integer (length of array Q) (Qlen>0)
   @param R output, remainder polynomial (an array of Fint elements)
   @param Rlen input integer (length of array R) (Rlen>=Alen)
   @param modulus input, a prime positive integer
   @throws ErrorInvalidArraySize or ErrorDivideByZero
*/
void polynomialDivide(const Fint A[], Int Alen,
                      const Fint B[], Int Blen,
                            Fint Q[], Int Qlen,
                            Fint R[], Int Rlen,
                            Fint modulus);



/**
   Implements Extended Euclid algorithm on two polynomials over a prime field.

   (See Chapter 2, Algorithm 2.221 in Handbook of Applied Cryptography,
   by Menezes, van Oorschot, Vanstone, CRC Press, 1996.)

   @param A input polynomial (an array of Fint elements)
   @param Alen input integer (length of array A) (Alen>0)
   @param B input polynomial (an array of Fint elements)
   @param Blen input integer (length of array B) (Blen>0)
   @param X output polynomial (an array of Fint elements)
   @param Xlen input integer (length of array X) (MUST HOLD: Xlen=Alen)
   @param Y output polynomial (an array of Fint elements)
   @param Ylen input integer (length of array Y) (MUST HOLD: Ylen=Alen)
   @param GCD output, greatest common divisor polynomial (an array of Fint elements)
   @param GCDlen input integer (length of array GCD) (MUST HOLD: GCDlen=Alen)
   @param modulus input, a prime positive integer
   @throws ErrorInvalidArraySize
*/
void polynomialExtendedEuclid(const Fint A[], Int Alen,
                              const Fint B[], Int Blen,
                                    Fint X[], Int Xlen,
                                    Fint Y[], Int Ylen,
                                    Fint GCD[], Int GCDlen,  //  GCD = A * X + B * Y
                                    Fint modulus);



/**
   Prints a polynomial
   @param A input array containing the source polynomial
   @param Alen input integer (length of array A)
*/
void polynomialPrint(const Fint A[], Int Alen);


//--------------------------------------------------
// Inline functions
//--------------------------------------------------

/**
   Determines degree of a polynomial (an input array)
   @param poly input array of type Fint containing polynomial coefficients
   @param len input integer (length of array poly)
   @returns degree of polynomial (returns -1 for the all zero polynomial)
*/
inline Int polynomialDegree(const Fint poly[], Int len)
{
   for (Int i=len-1; i>=0; i--)
   {
      if (poly[i]) return i;
   }

   return -1;
}


/**
   Sets a polynomial to the all zero polynomial
   @param poly input array (polynomial)
   @param len input integer (length of polynomial)
*/
inline void polynomialSetZero(Fint poly[], Int len)
{
   for (Int i=0; i<len; i++)
   {
      poly[i] = 0;
   }
}



/**
   Copies polynomial A to polynomial B
   @param A input array containing the source polynomial
   @param Alen input integer (length of array A)
   @param B output array containing the destination polynomial
   @param Blen input integer (length of array A)
*/
inline void polynomialCopy(const Fint A[], Int Alen, Fint B[], Int Blen)
{
   Int maxlen = (Alen>Blen) ? Alen : Blen;
   Int minlen = (Alen<Blen) ? Alen : Blen;

   for (Int i=0; i<minlen; i++)
   {
      B[i] = A[i];
   }

   if (maxlen == Blen)
   {
      for (Int i=minlen; i<maxlen; i++)
         B[i] = 0;
   }
}


} // namespace shk_galoiscpp

#endif