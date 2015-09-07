/**********************************************************************

       Project: C++ Library for General Galois Field Arithmetic

   Author: Saied H. Khayat
   Email:  shk@alum.wustl.edu
   Date:   February 2013

   Copyright Notice: Free use of this library is permitted under the
   guidelines and in accordance with the MIT License (MIT).
   http://opensource.org/licenses/MIT

**********************************************************************/

#include <iostream>
using namespace std;

#include <cassert>
#include "galoisfield.h"

namespace shk_galoiscpp
{

//------------------------------------------------------
GaloisField::GaloisField(Fint mod, Int dim, Fint poly[])
{
   assert (mod>1);
   assert (dim>0);

   modulus = mod;
   dimension = dim;
   reductpoly = new Fint[dimension+1];

   for (Int i=0; i < dimension+1; i++)
   {
      reductpoly[i] = poly[i];
   }
}


//------------------------------------------------------
GaloisField::~GaloisField()
{
   delete [] reductpoly;
}


//------------------------------------------------------
ostream& operator<<(ostream& output, const GaloisField& gf)
{
   output << "\nPrime Modulus: " << gf.modulus;
   output << "\nDimension: " << gf.dimension;

   output << "\nReduction Polynomial Coefficients: (";
   for (Int i=0; i<=gf.dimension; i++)
   {
      if (i < gf.dimension)
         output << gf.reductpoly[i] << " ";
      else
         output << gf.reductpoly[i] << ")\n";
   }

   return output;
}


} // namespace shk_galoiscpp
