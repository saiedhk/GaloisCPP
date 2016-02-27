/*******************************************************************************
   Project: C++ Library for General Galois Field Arithmetic

   Language: C++ 2007	   
   Author: Saied H. Khayat
   Date:   Feb 2013
   URL: https://github.com/saiedhk
   
   Copyright Notice: Free use of this library is permitted under the
   guidelines and in accordance with the MIT License (MIT).
   http://opensource.org/licenses/MIT

*******************************************************************************/

#include <cassert>
#include "modular_arith.h"

namespace shk_galoiscpp
{

// Computes greatest common divisor of two positive integers
void extendedEuclid(Fint a, Fint b, Fint& x, Fint& y, Fint& d)
{
   assert(a>0);
   assert(b>0);

   Fint q, r;
   Fint x1, x2, y1, y2;

   if (b==0)
   {
      d=a;
      x=1;
      y=0;
   }
   else
   {
      x1=0;
      x2=1;
      y1=1;
      y2=0;

      while (b > 0)
      {
         q = a / b;
         r = a % b;
         a = b;
         b = r;
         x = x2 - q * x1;
         y = y2 - q * y1;
         x2 = x1;
         x1 = x;
         y2 = y1;
         y1 = y;
      }
      d = a;
      x = x2;
      y = y2;
   }

} // end extendedEuclid


} // end namespace
