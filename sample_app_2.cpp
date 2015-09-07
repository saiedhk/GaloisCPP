/**********************************************************************

       Project: C++ Library for General Galois Field Arithmetic

   Author: Saied H. Khayat
   Email:  shk@alum.wustl.edu
   Date:   February 2013

   Copyright Notice: Free use of this library is permitted under the
   guidelines and in accordance with the MIT License (MIT).
   http://opensource.org/licenses/MIT

**********************************************************************/

// A non-trivial application of GaloisCPP library

// This program implements the Diffie-Hellmann Key Exchange Algorithm over
// a Galois Field with a relatively large prime modulus.

#include <iostream>
#include "gfelement.h"

using namespace std;
using namespace shk_galoiscpp;

#define PRIME 1008951599
#define DIM 6
// Therefore the Galois Field we are working with is GF(1008951599 ^ 6).
// This Galois Field has more than 10^60 elements.


int main()
{

   cout << "\n------------------------------------------------------\n";
   cout << "  DIFFIE-HELLMANN KEY EXCHANGE OVER A GALOIS FIELD";
   cout << "\n------------------------------------------------------\n";

   cout << "\n-------------Step 1---------------\n";
   cout << "Alice chooses a Galois Field with a large prime, a small dimension, and a\n";
   cout << "reduction polynomial of degree dimension+1.\n";

   // With the above modulus and dimension, it is known that the following
   // polynomial is irreducible. We choose it as the reduction polynomialthe Galois Field.
   Fint reduction_polynomial[DIM+1] = {1,1,1,1,1,1,1};

   // Declare a Galois Field
   GaloisField GF(PRIME, DIM, reduction_polynomial);
   cout << "\nLet's say Alice chose this Galois Field: " << GF << endl;

   cout << "\nAlice should also create at random a base Galois Field element G.\n";

   // Let's say this is the base polynomial G.
   Fint Gpoly[DIM] = {5017388,
                      18360017,
                      40011933,
                      8755039,
                      1237095,
                      49128817};

   // Create Galois Field Element G.
   GFelement G( &GF, Gpoly );
   cout << "Let's say Alice chose this base GFelement: " << G;

   cout << "Alice should send the Galois Field parameters (prime and dimension) to Bob.\n";
   cout << "Alice should also send Bob the base element G.\n";

   cout << "\n-------------Step 2---------------\n";
   cout << "Alice chooses a large random integer A and raises G to power A.\n";

   Fint A = 116441012; // a random number
   cout << "Let's say Alice chose A = : " << A << endl;

   cout << "Alice should raise G to power A and call it X.\n";
   GFelement X( &GF );   // create a GFelement X
   X = GFexp(G,A);       // raise G to power A.

   cout << "X = G^A = " << X << endl;

   cout << "Alice sends X to Bob.\n";

   cout << "\n-------------Step 3---------------\n";
   cout << "Bob chooses a large random integer B and raises G to power B.\n";

   Fint B = 1379921012; // a random number
   cout << "Let's say Bob chose B = : " << B << endl;

   cout << "Bob should raise G to power B and call it Y.\n";
   GFelement Y ( &GF );  // create a GFelement Y
   Y = GFexp(G,B);       // raise G to power B.

   cout << "Y = G^B = " << Y << endl;

   cout << "Bob sends Y to Alice.\n";

   cout << "\n-------------Step 4---------------\n";
   cout << "Alice should raise Y to power A and call it S_Alice.\n";

   GFelement S_Alice( &GF );   // create a GFelement S_Alice
   S_Alice = GFexp(Y,A);       // raise Y to power A.

   cout << "S_Alice = Y^A = " << S_Alice << endl;

   cout << "\n-------------Step 5---------------\n";
   cout << "Bob should raise X to power A and call it S_Alice.\n";

   GFelement S_Bob( &GF );   // create a GFelement S_Bob
   S_Bob = GFexp(X,B);       // raise X to power B.

   cout << "S_Bob = X^B = " << S_Bob << endl;

   cout << "\n-------------END---------------\n";
   cout << "The end result is that S_Alice should equal to S_Bob.\n";

   if (S_Alice == S_Bob)
   {
      cout << "Yes, S_Alice IS equal to S_Bob. All went ok!\n";
      cout << "Alice and Bob now have a shared secret called S = " << S_Alice;
   }
   else
   {
      cout << "Unfortunately, S_Alice is NOT equal to S_Bob!!!\n";
      cout << "Something went wrong!\n";
   }

   cout << "Caveat: To be secure, Diffie-Hellmann Key Exchange requires that the prime modulus\n";
   cout << "be well over 100 bits length. But GaloisCPP's modulus can only be up to\n";
   cout << "64 bits (the size of long long int).\n";

   return 0;
}
