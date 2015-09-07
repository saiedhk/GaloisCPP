# galoiscpp
GaloisCPP: C++ Library for General Galois Field Arithmetic

This C++ library provides classes and operators for arithmetic operations
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