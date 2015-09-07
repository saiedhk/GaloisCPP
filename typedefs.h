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
   Basic definitions for the Galois Field Package
*/

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

/**
   To avoid future naming conflicts, this entire library has been placed in
   the namespace 'shk_galoiscpp;.
*/
namespace shk_galoiscpp
{

/**
   'Fint' is the basic integer type used for field elements.
   This typedef allows one to set 'Fint' to any integer type. However,
   IMPORTANT NOTE: The integer type chosen for 'Fint' MUST be of signed type.
*/
typedef signed long long int Fint;


/**
   'Int' is the integer type used for array indices and field dimension.
   This typedef allows one to set 'Int' to any integer type. However,
   it is perhaps unnecessary and impractical to set the dimension of a field to
   large numbers because the complexity of computations grows superlinearly
   with field dimension.
*/
typedef signed short Int;


/**
   Defines error/exception codes
   @param OK means no error happened.
   @param ErrorIncompatibleFields mean the two numbers or elements are from two different fields.
   @param ErrorNoInverse means the number or element does not have a multiplicative inverse.
   @param ErrorDivideByZero means divide by zero happened.
   @param ErrorInvalidArraySize means one or more of arrays in function argument have invalid size.
*/
typedef enum
{
   OK,                      // No error
   ErrorIncompatibleFields, // The two number or element are from two different fields.
   ErrorNoInverse,          // The number of element does not have a multiplicative inverse.
   ErrorDivideByZero,       // Divide by zero happened.
   ErrorInvalidArraySize    // One or more of arrays in function argument have invalid size.
} ErrorCode;


} // namespace shk_galoiscpp

#endif