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

#include <iostream>
using namespace std;

#include "polynomial_arith.h"

namespace shk_galoiscpp
{


//---------------------------------------------------------
// Polynomial Addition
//---------------------------------------------------------
void polynomialAdd(const Fint A[], Int Alen,
                   const Fint B[], Int Blen,
                         Fint S[], Int Slen,  // S = A + B
                         Fint modulus)
{
   Int maxlen = (Alen>Blen) ? Alen : Blen;
   Int minlen = (Alen<Blen) ? Alen : Blen;

   assert(Alen>0 && Blen>0);
   assert(Slen>=maxlen);

   // check array sizes
   if ( !(Alen>0 && Blen>0 && Slen>=maxlen) )
   {
      throw ErrorInvalidArraySize;
   }

   // set sum polynomial to zero
   polynomialSetZero(S, Slen);

   // do the summation
   for (Int i=0; i<minlen; i++)
   {
      S[i] = addModular(A[i], B[i], modulus);
   }

   for (Int i=minlen; i<maxlen; i++)
   {
      if (maxlen==Alen)
         S[i] = A[i];
      else
         S[i] = B[i];
   }
}



//---------------------------------------------------------
// Polynomial Subtraction
//---------------------------------------------------------
void polynomialSubtract(const Fint A[], Int Alen,
                        const Fint B[], Int Blen,
                              Fint D[], Int Dlen,  // D = A - B
                              Fint modulus)
{
   Int maxlen = (Alen>Blen) ? Alen : Blen;
   Int minlen = (Alen<Blen) ? Alen : Blen;

   assert(Alen>0 && Blen>0);
   assert(Dlen>=maxlen);

   // check array sizes
   if ( !(Alen>0 && Blen>0 && Dlen>=maxlen) )
      throw ErrorInvalidArraySize;

   // set difference polynomial to zero
   polynomialSetZero(D, Dlen);

   // do the subtraction
   for (Int i=0; i<minlen; i++)
   {
      D[i] = subtractModular(A[i], B[i], modulus);
   }

   for (Int i=minlen; i<maxlen; i++)
   {
      if (maxlen == Alen)
         D[i] = A[i];
      else
         D[i] = ( (B[i]>0) ? (modulus - B[i]) : 0);
   }
}



//---------------------------------------------------------
// Polynomial multiplication
//---------------------------------------------------------
void polynomialMultiply(const Fint A[], Int Alen,
                        const Fint B[], Int Blen,
                              Fint P[], Int Plen,  // P = A * B
                              Fint modulus)
{
   assert(Alen>0 && Blen>0 && Plen>0);
   assert(Plen>=Alen+Blen-1);

   // check array sizes
   if ( !(Alen>0 && Blen>0 && Plen>0 && Plen>=Alen+Blen-1) )
      throw ErrorInvalidArraySize;

   // set product polynomial to zero
   polynomialSetZero(P, Plen);

   // get the degree of multiplicands
   Int Adeg = polynomialDegree(A, Alen);
   Int Bdeg = polynomialDegree(B, Blen);

   for (Int i=0; i<=Adeg + Bdeg; i++)
   {
      for (Int j=0; j<=i; j++)
      {
         if ( (i-j <= Bdeg) && (j <= Adeg) )
         {
            Fint temp = multiplyModular(A[j], B[i-j], modulus);
            P[i] = addModular(P[i], temp, modulus);
         }
      }
   }
}



//---------------------------------------------------------
// Polynomial Long Division
//---------------------------------------------------------
void polynomialDivide(const Fint A[], Int Alen,
                      const Fint B[], Int Blen,
                            Fint Q[], Int Qlen,
                            Fint R[], Int Rlen,
                            Fint modulus)
{
   assert(Alen>0 && Blen>0);
   assert(Qlen>=Alen);
   assert(Rlen>=Alen);

   // check array sizes
   if ( !(Alen>0 && Blen>0 && Qlen>=Alen && Rlen>=Alen) )
      throw ErrorInvalidArraySize;

   // determine degree of A and B
   Int Adeg = polynomialDegree(A,Alen);
   Int Bdeg = polynomialDegree(B,Blen);

   //------ first take care of sepcial cases -------
   if (Bdeg==-1) // polynomial B is zero
   {
      throw ErrorDivideByZero;  // return error
   }

   if (Adeg==-1) // polynomial A is zero
   {
      polynomialSetZero(Q,Qlen);
      polynomialSetZero(R,Rlen);
      return;
   }

   //-------- now begin the long division ---------

   // allocate array to hold result of B multplied by q
   Fint* qB = new Fint[Adeg+1];

   // set Q and R to zero
   polynomialSetZero(Q,Qlen);
   polynomialSetZero(R,Rlen);

   // copy A to R
   Int Rdeg = Adeg;
   polynomialCopy(A,Adeg+1,R,Rdeg+1);

   while ( Rdeg >= Bdeg )
   {
      Fint q = divideModular(R[Rdeg], B[Bdeg], modulus); // divide leading coefficients

      Int diff = Rdeg - Bdeg;

      // update Q
      Q[diff] = q;

      // do this: qB = q * B
      for (Int i=Bdeg; i>=0; i--)
      {
         qB[i+diff] = multiplyModular(B[i], q, modulus);
      }
      for (Int i=0; i<diff; i++)
      {
         qB[i] = 0;
      }

      // now do this: R = R - q*B
      for (Int i=0; i<=Rdeg; i++)
      {
         R[i] = subtractModular(R[i], qB[i], modulus);
      }

      // determine degree of R
      Rdeg = polynomialDegree(R,Rlen);

   } // end while

   delete [] qB;
}


//---------------------------------------------------------
// Extended Euclid algorithm for polynomials
void polynomialExtendedEuclid(const Fint A[], Int Alen,
                              const Fint B[], Int Blen,
                                    Fint X[], Int Xlen,
                                    Fint Y[], Int Ylen,
                                    Fint GCD[], Int GCDlen,  //  GCD = A * X + B * Y
                                    Fint modulus)
{
   assert(Alen>0);
   assert(Blen>0);
   assert(Xlen>0);
   assert(Ylen>0);
   assert(GCDlen>0);
   assert(Xlen==Alen);
   assert(Ylen==Alen);
   assert(GCDlen==Alen);

   if ( !(Alen>0 && Blen>0 && Xlen>0 && Ylen>0 && GCDlen>0 &&
          Xlen==Alen && Ylen==Alen && GCDlen==Alen) )
   {
      throw ErrorInvalidArraySize;
   }

   // determine degree of B
   Int Bdeg = polynomialDegree(B,Blen);

   if (Bdeg==-1) // if B is zero polynomial
   {
      polynomialCopy(A,Alen,GCD,GCDlen);   // GCD = A
      polynomialSetZero(Y,Ylen);           // Y = 0
      polynomialSetZero(X,Xlen); X[0] = 1; // X = 1
      return;
   }
   else // if B is a nonzero polynomial
   {
      Int Qlen, Rlen, Tlen, Dlen;
      Qlen = Rlen = Alen;
      Tlen = Dlen = Qlen + Xlen;

      Fint* Alocal = new Fint[Alen];
      Fint* Blocal = new Fint[Blen];
      Fint* X1 = new Fint[Xlen];
      Fint* X2 = new Fint[Xlen];
      Fint* Y1 = new Fint[Ylen];
      Fint* Y2 = new Fint[Ylen];
      Fint* Q  = new Fint[Qlen];
      Fint* R  = new Fint[Rlen];
      Fint* T  = new Fint[Tlen];
      Fint* D  = new Fint[Dlen];

      // make local copies of A and B so the originals don't change
      polynomialCopy(A, Alen, Alocal, Alen);  // Alocal = A
      polynomialCopy(B, Blen, Blocal, Blen);  // Blocal = B

      polynomialSetZero(X1,Xlen);             // X1 = 0
      polynomialSetZero(X2,Xlen); X2[0] = 1;  // X2 = 1
      polynomialSetZero(Y1,Ylen); Y1[0] = 1;  // Y1 = 1
      polynomialSetZero(Y2,Ylen);             // Y2 = 0

      while (Bdeg >= 0) // while B is nonzero polynomial
      {

         // divide A by B  (such that A = B * Q + R)
         polynomialDivide(Alocal, Alen,
                          Blocal, Blen,
                          Q, Qlen,
                          R, Rlen,
                          modulus);

         polynomialCopy(Blocal, Blen, Alocal, Alen); // Alocal = Blocal
         polynomialCopy(R, Rlen, Blocal, Blen);      // Blocal = R
         Bdeg = polynomialDegree(Blocal, Blen);

         polynomialMultiply(X1, Xlen, Q, Qlen, T, Tlen, modulus);  // T = Q * X1
         polynomialSubtract(X2, Xlen, T, Tlen, D, Dlen, modulus);  // D = X2 - T
         polynomialCopy(D, Dlen, X, Xlen);                         // X = D

         polynomialMultiply(Y1, Ylen, Q, Qlen, T, Tlen, modulus);  // T = Q * Y1
         polynomialSubtract(Y2, Ylen, T, Tlen, D, Dlen, modulus);  // D = Y2 - T
         polynomialCopy(D, Dlen, Y, Ylen);                         // Y = D

         polynomialCopy(X1, Xlen, X2, Xlen); // X2 = X1
         polynomialCopy(X,  Xlen, X1, Xlen); // X1 = X

         polynomialCopy(Y1, Ylen, Y2, Ylen); // Y2 = Y1
         polynomialCopy(Y,  Ylen, Y1, Ylen); // Y1 = Y

      } // end while

      polynomialCopy(Alocal, Alen, GCD, GCDlen);   // GCD = Alocal
      polynomialCopy(X2, Xlen, X, Xlen);           // X = X2
      polynomialCopy(Y2, Ylen, Y, Ylen);           // Y = Y2

      delete [] Alocal;
      delete [] Blocal;
      delete [] X1;
      delete [] X2;
      delete [] Y1;
      delete [] Y2;
      delete [] Q;
      delete [] R;
      delete [] T;
      delete [] D;

   } // end if

} // end function




//  Print a polynomial
void polynomialPrint(const Fint A[], Int Alen)
{
   Int Adeg = polynomialDegree(A,Alen);

   if (Adeg==-1)
   {
      cout << "( 0 )\n";
   }
   else
   {
      cout << "( ";
      for (Int i=Adeg; i>=0; i--)
      {
         if (i>0)
            cout << A[i] << " x^" << i << " + ";
         else
            cout << A[i] << " )\n";
      }

   }
}



} // namespace shk_galoiscpp
