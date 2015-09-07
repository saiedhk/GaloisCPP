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

#include "gfelement.h"

namespace shk_galoiscpp
{


//-----------------------------------------------------------------------------
// Constructors and destructors
//-----------------------------------------------------------------------------

GFelement::GFelement(GaloisField* gf)
{
   field = gf;
   modulus = field->getModulus();
   dimension = field->getDimension();
   polynomial = new Fint[dimension];
}


//------------------------------------------------------
GFelement::GFelement(GaloisField* gf, const Fint* coeff)
{
   field = gf;
   modulus = field->getModulus();
   dimension = field->getDimension();
   polynomial = new Fint[dimension];

   for (Int i=0; i<dimension; i++)
   {
      setCoefficient(i,coeff[i]);
   }
}


//------------------------------------------------------
GFelement::GFelement(const GFelement& gfe)
{
   field = gfe.field;
   modulus = gfe.modulus;
   dimension = gfe.dimension;
   polynomial = new Fint[dimension];

   for (Int i=0; i<dimension; i++)
   {
      polynomial[i] = gfe.polynomial[i];
   }
}


//------------------------------------------------------
GFelement::~GFelement()
{
   delete [] polynomial;
}


//-----------------------------------------------------------------------------
// mutators
//-----------------------------------------------------------------------------

void GFelement::setZero(void)
{
   for (Int i=0; i<dimension; i++)
   {
      polynomial[i] = 0;
   }
}



//------------------------------------------------------
void GFelement::setOne(void)
{
   polynomial[0] = 1;

   for (Int i=1; i<dimension; i++)
   {
      polynomial[i] = 0;
   }
}



//-----------------------------------------------------------------------------
// operators
//-----------------------------------------------------------------------------

Fint& GFelement::operator[](Int index)
{
   return polynomial[index];
}



//------------------------------------------------------
Fint GFelement::operator[](Int index) const
{
   return polynomial[index];
}



//------------------------------------------------------
GFelement& GFelement::operator=(const GFelement& right)
{
   if (this != &right)
   {
      field = right.field;
      modulus = right.modulus;
      dimension = right.dimension;

      // deallocate and reallocate polynomial of this GFelement
      delete [] polynomial;
      polynomial = new Fint[dimension];

      for (Int i=0; i<dimension; i++)
      {
         polynomial[i] = right.polynomial[i];
      }
   }
   return *this;
}



//------------------------------------------------------
GFelement GFelement::operator-()
{
   GFelement result(field);

   for (Int i=0; i<dimension; i++)
   {
      result.polynomial[i] = (polynomial[i]>0) ? (modulus - polynomial[i]) : 0;
   }

   return result;
}



//------------------------------------------------------
bool operator==(const GFelement& left, const GFelement& right)
{
   if (left.field != right.field) throw ErrorIncompatibleFields;

   bool isequal = true;

   for (Int i=0; i<left.dimension; i++)
   {
      if (left.polynomial[i] != right.polynomial[i])
      {
         isequal = false;
      }
   }

   return isequal;
}



//------------------------------------------------------
bool operator!=(const GFelement& left, const GFelement& right)
{
   if (left.field != right.field) throw ErrorIncompatibleFields;

   bool isequal = true;

   for (Int i=0; i<left.dimension; i++)
   {
      if (left.polynomial[i] != right.polynomial[i])
      {
         isequal = false;
      }
   }

   return !(isequal);
}



//------------------------------------------------------
bool operator<(const GFelement& left, const GFelement& right)
{
   if (left.field != right.field) throw ErrorIncompatibleFields;

   bool isless = false;

   for (Int i=left.dimension-1; i>=0; i--)
   {
      if (left.polynomial[i] < right.polynomial[i])
      {
         isless = true;
         break;
      }
      else if (left.polynomial[i] > right.polynomial[i])
      {
         isless = false;
         break;
      }
   }

   return isless;
}



//------------------------------------------------------
bool operator>(const GFelement& left, const GFelement& right)
{
   if (left.field != right.field) throw ErrorIncompatibleFields;

   bool isgreater = false;

   for (Int i=left.dimension-1; i>=0; i--)
   {
      if (left.polynomial[i] > right.polynomial[i])
      {
         isgreater = true;
         break;
      }
      else if (left.polynomial[i] < right.polynomial[i])
      {
         isgreater = false;
         break;
      }
   }

   return isgreater;
}



//------------------------------------------------------
bool operator<=(const GFelement& left, const GFelement& right)
{
   if (left.field != right.field) throw ErrorIncompatibleFields;

   return ((left==right) | (left<right)) ? true : false;
}



//------------------------------------------------------
bool operator>=(const GFelement& left, const GFelement& right)
{
   if (left.field != right.field) throw ErrorIncompatibleFields;

   return ((left==right) | (left>right)) ? true : false;
}



//------------------------------------------------------
GFelement operator+(const GFelement& left, const GFelement& right)
{
   if (left.field != right.field) throw ErrorIncompatibleFields;

   GFelement result(left.field);

   for (Int i=0; i<left.dimension; i++)
   {
      result.polynomial[i] = addModular(left.polynomial[i],
                                        right.polynomial[i],
                                        left.modulus);
   }

   return result;
}



//------------------------------------------------------
GFelement operator-(const GFelement& left, const GFelement& right)
{
   if (left.field != right.field) throw ErrorIncompatibleFields;

   GFelement result(left.field);

   for (Int i=0; i<left.dimension; i++)
   {
      result.polynomial[i] = subtractModular(left.polynomial[i],
                                             right.polynomial[i],
                                             left.modulus);
   }

   return result;
}



//------------------------------------------------------
GFelement operator*(const GFelement& left, const GFelement& right)
{
   if (left.field != right.field) throw ErrorIncompatibleFields;

   Int dim = left.dimension;
   Fint modulus = left.modulus;

   Fint* product = new Fint[2*dim-1]; // allocate to store product of two GFelements
   Fint* R = new Fint[2*dim-1];       // allocate remainder polynomial
   Fint* Q = new Fint[2*dim-1];       // allocate quotient polynomial
   Fint* reductionpolynomial = new Fint[dim+1];

   // multiply two polynomials left and right
   polynomialMultiply(left.polynomial, dim,
                      right.polynomial, dim,
                      product, 2*dim-1,
                      modulus);

   // copy the reduction polynomial from GaloisField associated with this GFelement
   for (Int i=0; i<dim+1; i++)
   {
      reductionpolynomial[i] = left.field->reductionPolynomial(i);
   }

   // reduce the product polynomial by the reduction polynomial
   polynomialDivide(product, 2*dim-1,
                    reductionpolynomial, dim+1,
                    Q, 2*dim-1,
                    R, 2*dim-1,
                    modulus);

   // R polynomial is the result to be returned
   GFelement result(left.field,R);

   // deallocate local polynomials
   delete [] R;
   delete [] Q;
   delete [] product;
   delete [] reductionpolynomial;

   return result;
}



//------------------------------------------------------
GFelement operator/(const GFelement& left, const GFelement& right)
{
   if (left.field != right.field)
   {
      throw ErrorIncompatibleFields;
   }

   return  left * GFmultInverse( right );
}



//------------------------------------------------------
GFelement operator*(Fint left, const GFelement& right)
{
   GFelement result(right.field);

   for (Int i=0; i<right.dimension; i++)
   {
      result.polynomial[i] = multiplyModular(left, right.polynomial[i], right.modulus);
   }

   return result;
}



//------------------------------------------------------
GFelement operator*(const GFelement& left, Fint right)
{
   GFelement result(left.field);

   for (Int i=0; i<left.dimension; i++)
   {
      result.polynomial[i] = multiplyModular(right, left.polynomial[i], left.modulus);
   }

   return result;
}



//------------------------------------------------------
GFelement operator/(const GFelement& left, Fint right)
{
   GFelement result(left.field);

   for (Int i=0; i<left.dimension; i++)
   {
      result.polynomial[i] = divideModular(left.polynomial[i], right, left.modulus);
   }

   return result;
}



//------------------------------------------------------
ostream& operator<<(ostream& output, const GFelement& right)
{
   output << "(";
   for (Int i=0; i<right.dimension; i++)
   {
      if (i < right.dimension-1)
         output << right.polynomial[i] << " ";
      else
         output << right.polynomial[i] << ")\n";
   }

   return output;
}



//------------------------------------------------------
GFelement GFmultInverse(const GFelement& gfe)
{
   Int dim = gfe.dimension;
   Fint modulus = gfe.modulus;

   Fint* reductionpolynomial = new Fint[dim+1];
   Fint* inversepoly = new Fint[dim+1]; // allocate to store inverse of right polynomial
   Fint* dummy = new Fint[dim+1];       // allocate a dummay polynomial
   Fint* gcd = new Fint[dim+1];         // allocate to store gcd
   Fint* product = new Fint[2*dim-1];   // allocate to store product
   Fint* R = new Fint[2*dim-1];         // allocate remainder polynomial
   Fint* Q = new Fint[2*dim-1];         // allocate quotient polynomial

   // get reduction polynomial from GF associated with this GFelement
   for (Int i=0; i<dim+1; i++)
   {
      reductionpolynomial[i] = gfe.field->reductionPolynomial(i);
   }

   // determine inverse of gfe.polynomial (calling it inverse)
   polynomialExtendedEuclid(reductionpolynomial, dim+1,
                            gfe.polynomial, dim,
                            dummy, dim+1,
                            inversepoly, dim+1,
                            gcd, dim+1,
                            modulus);

   // check to make sure if gcd is 1
   Int degGcd = polynomialDegree(gcd,dim+1);

   // if degree of gcd is not 0, or if it is the zero polynomial, then throw exception
   if ( degGcd > 0 || gcd[0]==0 )
   {
      throw ErrorNoInverse;
   }


   if (gcd[0] > 1) // if gcd is a scalar that is not equal to 1, then
                   // inversepoly must be divided by gcd.
   {
      Fint invgcd = inverseModular(gcd[0],modulus);

      for (Int i=0; i<dim; i++)
      {
         inversepoly[i] = multiplyModular(inversepoly[i], invgcd, modulus);
      }
   }

   // polynomial R is the result to be returned.
   GFelement result(gfe.field,inversepoly);

   // deallocate local polynomials
   delete [] R;
   delete [] Q;
   delete [] dummy;
   delete [] gcd;
   delete [] inversepoly;
   delete [] product;
   delete [] reductionpolynomial;

   return result;
}



//------------------------------------------------------
GFelement GFexp(const GFelement& G, Fint m)
{
   GFelement S( G.getField() ); // create S to be in the same field as G

   S.setCoefficients(0); S[0] = 1; // set to S(x)=1

   if (m == 0) return S;

   GFelement Gtemp( G.getField() ); // create G in the same field as g
   Gtemp = G; // set Gtemp(x) = G(x)

   Fint mask = 1;

   if (m & mask)
   {
      S = G;
   }

   for (Int i=0; i < static_cast<signed>(8*sizeof(Fint)); i++)
   {
      Gtemp = Gtemp * Gtemp;
      mask <<= 1;
      if (m & mask)
      {
         S = Gtemp * S;
      }
   }

   return S;
}

//------------------------------------------------------


} // namespace
