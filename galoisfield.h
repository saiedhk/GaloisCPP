/**********************************************************************

       Project: C++ Library for General Galois Field Arithmetic

   Author: Saied H. Khayat
   Email:  shk@alum.wustl.edu
   Date:   February 2013

   Copyright Notice: Free use of this library is permitted under the
   guidelines and in accordance with the MIT License (MIT).
   http://opensource.org/licenses/MIT

**********************************************************************/

#ifndef GALOISFIELD_H
#define GALOISFIELD_H

#include "typedefs.h"
#include <cassert>


namespace shk_galoiscpp
{

/**
   This class defines a Galois Field of characteristic p and dimesion k (for GF(p^k)).
   It stores the following (private) data about the field:
   @param modulus The modulus (aka the characteristics p), which MUST be a prime number.
   @param dimension The dimension (k) of Galois Field (a nonzero positive integer).
   @param reductpoly A polynomial of degree k over the prime field GF(p). This polynomial
   MUST be irreducible. The program does not check this. YOU MUST correctly choose
   this polynomial.

   The attributes of a GaloisField are set when it is instantiated.
   Once instantiated, the attributes of cannot be changed.
*/
class GaloisField
{
   public:

      //---------------------------
      // constructors
      //---------------------------
      /**
         Constructs a Galois Field (GF)
         @param mod a positive prime integer (the modulus of GF)
         @param dim a positive integer (the dimension of GF)
         @param poly an array of length dim(the reduction polynomial of GF)
         (must be an irreducible polynomial over the prime field of GF)
      */
      GaloisField(Fint mod, Int dim, Fint poly[]);

      /**
         Destructs GaloisField, freeing allocated space for reduction polynomial in it.
      */
      ~GaloisField();

      //---------------------------
      // accessors
      //---------------------------

      /**
         Returns modulus of GF.
      */
      Fint getModulus() const;

      /**
         Returns dimension of GF
      */
      Int getDimension() const;

      /**
         Returns i-th coefficient of reduction polynomial of GF
      */
      Fint reductionPolynomial(Int i) const;

      /**
         Outputs information about this Galois Field to the standard output.
         @param gf GaloisField on the right of << sign
         @param output an output stream on the left of << sign
         @returns output stream
      */
      friend ostream& operator<<(ostream& output, const GaloisField& gf);

   private:
      Fint modulus;      // prime modulus (characteristic) of Galois Field
      Int dimension;     // dimension of Galois Field
      Fint* reductpoly;  // reduction polynomial of Galois Field
};




//--------------------------------------
// Inline class functions
//--------------------------------------

inline Fint GaloisField::getModulus() const
{
   return modulus;
}


inline Int GaloisField::getDimension() const
{
   return dimension;
}


inline Fint GaloisField::reductionPolynomial(Int i) const
{
   return reductpoly[i];
}



} // namespace shk_galoiscpp

#endif
