*******************************************************************************
Package Name: GaloisCPP
Brief Description: C++ Library for General Galois Field Arithmetic

Language: C++ (2007)
Version: 0.9
License: Microsoft Public License (MS-PL)

Developer: Saied H. Khayat
Email:  shk@alum.wustl.edu
Date started: Feb 2013

   Copyright Notice: Free use of this library is permitted under the
   guidelines and in accordance with the MIT License (MIT).
   http://opensource.org/licenses/MIT

*******************************************************************************

Project Description
-------------------

This is a C++ library providing classes and operators for arithmetic operations
on general finite field elements. A field is an algebraic structure in which the
operations of addition, subtraction, multiplication, and division (except by
zero) can be performed, and satisfy the familiar rules of closure,
commutativity, associativity and distributivity.

A finite field is a field containing a finite number of elements. The order of a
finite field is the number of elements in the field. There exists a finite field
F of order q if and only if q is a prime power, i.e., q = p^m, where p is a
prime number, and m is a positive integer. The prime p is called the
characteristic and m is called the dimension of the field. When m=1,  F is
called a prime field, denoted GF(p). If m>1 , then F is called an extension
field, denoted GF(p^m). The most widely used finite fields are those with
characteristic 2, also called the binary finite fields GF(2^m). However, there
are applications that benefit from the use of general finite fields GF(p^m).

Finite field theory (aka Galois theory in honor of Évariste Galois) is part of
the discipline of abstract algebra, and has found interesting applications in
cryptography and error-control coding.  Galois was a brilliant French
mathematician who lived in the 18th century and made some great contributions to
algebra before dying at the age of 20!

This C++ library aims at providing classes and overloaded operators for
arithmetic operations on elements of general finite fields GF(p^m). Arithmetic
in a finite field is different from standard integer arithmetic. Therefore the
usual arithmetic operators have to be redefined/overloaded in C++. While there
are software packages in C, C++ and other languages for the binary finite
fields, the library presented here handles the general case, i.e., GF(p^m). In
this library, the characteristic p of the finite field is a class parameter that
can be set to any prime integer limited only by the computer's integer word. To
promote maximum portability, this library is written in standard C++.



Source Code Overview
--------------------

The GaloisCPP package consists of the following C++ source files:

    1. readme.txt: This file contains the general information about the package.

    2. typedefs.h: This file contains type definitions for the entire library,
    including Fint (field integer).

    3. modular_arith.h: This header file contains the required functions for
    performing modular arithmetic on the underlying field integers (i.e.,
    Fints).

    4. modular_arith.cpp: This file contains the implementation of the functions
    declared in modular_arith.h file.

    5. polynomial_arith.h: This header file contains the required functions for
    performing arithmetic operations on polynomials.

    6. polynomial_arith.cpp: This file contains the implementation of the
    functions declared in polynomial_arith.h file.

    7. galoisfield.h: This header file contains the class and method definitions
    required to create and configure a GaloisField.

    8. galoisfield.cpp: This file contains the implementation of methods
    declared in the galoisfield.h file.

    9. gfelement.h: This header file contains the class and method definitions
    required to create and configure Galois field elements, i.e., GFelements.

    10. galoisfield.cpp: This file contains the implementation of methods
    declared in the gfelement.h file.

The following C++ programs has been developed to test and to demo the package.

    1. test_gfelement: This file is a test program to exercise the functionality
    of GaloisField and GFelement classes.

    2. test_gfelement.in: The input file for test_gfelement.cpp.

    3. test_gfelement.out: The output of test_gfelement.cpp.

    4. sample_app_1.cpp: A basic sample program to jumpstart the users.

    5. sample_app_2.cpp: A sample application program (Diffie-Hellmann Key Exchange
    over Galois Field). 

    6. sample_app_3.cpp: A demo command-line Galois Field Calculator (To be done). 

    7. Makefile:  This file specifies how to compile and build the library and
    the sample applications.

A complete set of Javadoc style hypertext documentations for the entire package
is available in the following file which is included in the package (just unzip
it and start from index.htm):

    o GaloisCPP_documentation.zip

All the source code has been developed and tested on Microsoft Visual Studio
.NET 2010. It has been also compiled and tested on GNU C++ 4.5.2.

This package is ready for use, but I consider it as work in progress, and plan
to improve and expand it when I finds the time. If you have any suggestions, bug
reports or corrections or if this library interests you in any way, I’d be glad
to hear from you. I hope you will enjoy using it as I enjoyed developing it.

Saied H. Khayat
Email: shk@alum.wustl.edu



