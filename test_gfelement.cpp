/**********************************************************************

       Project: C++ Library for General Galois Field Arithmetic

   Author: Saied H. Khayat
   Email:  shk@alum.wustl.edu
   Date:   February 2013

   Copyright Notice: Free use of this library is permitted under the
   guidelines and in accordance with the MIT License (MIT).
   http://opensource.org/licenses/MIT

**********************************************************************/

// Program to test GFelement Class

#include <iostream>
#include "gfelement.h"

using namespace std;
using namespace shk_galoiscpp;


int main()
{
   Int sentinel;
   Fint modulus;
   Int dimension;
   Fint *Apoly, *Bpoly, *Cpoly, *Dpoly, *reductpoly;
   Fint a, b;

   while (1) {
      cin >> sentinel;
      if (sentinel<1) break; // break while(1)

      cin >> modulus;
      cin >> dimension;

      reductpoly = new Fint[dimension+1];
      for (int i=0; i<dimension+1; i++) cin >> reductpoly[i];

      // Define Galois Field
      GaloisField gf(modulus, dimension, reductpoly);
      cout << gf;
      //---------------------------------

      GFelement ZERO(&gf);
      ZERO.setZero();
      cout << "ZERO = " << ZERO;

      GFelement ONE(&gf);
      ONE.setOne();
      cout << "ONE = " << ONE;

      GFelement E(&gf), F(&gf), G(&gf), H(&gf);

      // initialize from standard input
      cin >> a >> b;
      cout << "a=" << a << "  b=" << b << endl;

      Apoly = new Fint[dimension];
      for (int i=0; i<dimension; i++) cin >> Apoly[i];

      Bpoly = new Fint[dimension];
      for (int i=0; i<dimension; i++) cin >> Bpoly[i];

      Cpoly = new Fint[dimension];
      for (int i=0; i<dimension; i++) cin >> Cpoly[i];

      Dpoly = new Fint[dimension];
      for (int i=0; i<dimension; i++) cin >> Dpoly[i];

      GFelement A(&gf,Apoly);
      GFelement B(&gf,Bpoly);
      GFelement C(&gf,Cpoly);
      GFelement D(&gf);
      for (int i=0; i<dimension; i++) D.setCoefficient(i,Dpoly[i]);

      cout << "A: " << A;
      cout << "B: " << B;
      cout << "C: " << C;
      cout << "D: " << D;

      //*********************** action begins ************************

      try
      {
         cout << "\nACTION: E = A + B\n";
         E = A + B;
         cout << "RESULT: E = " << E;
      }
      catch(ErrorCode e) { cout << e << endl; }

      //-------------------------------------------------------------
      cout << "\nACTION: Check equality operator: is E == E ?\n";
      if (E==E)
         cout << "\nOK: E==E is true\n";
      else
         cout << "\nERROR: E==E is false\n";

      cout << "\nACTION: Check inequality operator: is E != E ?\n";
      if (E != E)
         cout << "\nERROR: E != E is true\n";
      else
         cout << "\nOK: E != E is false\n";

      //-------------------------------------------------------------
      cout << "\nACTION: Check inequality operators on A and B.\n";
      if (A < B)
         cout << "\nA < B is true\n";
      else
         cout << "\nA < B is false\n";

      if (A > B)
         cout << "\nA > B is true\n";
      else
         cout << "\nA > B is false\n";

      if (A <= B)
         cout << "\nA <= B is true\n";
      else
         cout << "\nA <= B is false\n";

      if (A >= B)
         cout << "\nA >= B is true\n";
      else
         cout << "\nA >= B is false\n";

      //-------------------------------------------------------------
      cout << "\nACTION: Check inequality operators on C and D.\n";
      if (C < D)
         cout << "\nC < D is true\n";
      else
         cout << "\nC < D is false\n";

      if (C > D)
         cout << "\nC > D is true\n";
      else
         cout << "\nC > D is false\n";

      if (C <= D)
         cout << "\nC <= D is true\n";
      else
         cout << "\nC <= D is false\n";

      if (C >= D)
         cout << "\nC >= D is true\n";
      else
         cout << "\nC >= D is false\n";

      //-------------------------------------------------------------
      cout << "\nACTION: E = -A\n";
      E = -A;
      cout << "RESULT: E = " << E;

      cout << "\nACTION: F = -E\n";
      F = -E;
      cout << "RESULT: F = " << F;


      if (F==A)
         cout << "\nOK: F==A is true\n";
      else
         cout << "\nERROR: F==A is false\n";


      //-------------------------------------------------------------
      cout << "\nACTION: copy constructor: GFelement CopyofD(D)\n";
      GFelement CopyofD(D);
      cout << "RESULT: CopyofD = " << CopyofD;


      if (CopyofD==D)
         cout << "\nOK: CopyofD==D is true\n";
      else
         cout << "\nNOT OK: CopyofD==D is false\n";


      //-------------------------------------------------------------
      try
      {
         cout << "\nACTION: F = C - D\n";
         F = C - D;
         cout << "RESULT: F = " << F;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try
      {
         cout << "\nACTION: E = D + F\n";
         E = D + F;
         cout << "RESULT: E = " << E;
      }
      catch(ErrorCode e) { cout << e << endl; }

      if (C==E)
         cout << "\nOK: C==E is true\n";
      else
         cout << "\nERROR: C==E is false\n";

      //-------------------------------------------------------------
      try
      {
         cout << "\nACTION: F = A * B\n";
         F = A * B;
         cout << "RESULT: F = " << F;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try
      {
         cout << "\nACTION: E = F / A\n";
         E = F / A;
         cout << "RESULT: E = " << E;
      }
      catch(ErrorCode e) { cout << e << endl; }

      if (B==E)
         cout << "\nOK: B==E is true\n";
      else
         cout << "\nERROR: B==E is false\n";


      //-------------------------------------------------------------
      try
      {
         cout << "\nACTION: F = A / B\n";
         F = A / B;
         cout << "RESULT: F = " << F;
      }
      catch(ErrorCode e) { cout << e << endl; }


      try
      {
         cout << "\nACTION: E = F * B\n";
         E = F * B;
         cout << "RESULT: E = " << E;
      }
      catch(ErrorCode e) { cout << e << endl; }


      if (A==E)
         cout << "\nOK: A==E is true\n";
      else
         cout << "\nERROR: A==E is false\n";


      //-------------------------------------------------------------
      try {
         cout << "\nACTION: E = a * B\n";
         E = a * B;
         cout << "RESULT: E = " << E;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: F = A * b\n";
         F = A * b;
         cout << "RESULT: F = " << F;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: G = E + F\n";
         G = E + F;
         cout << "RESULT: G = " << G;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: E = B * a\n";
         E = B * a;
         cout << "RESULT: E = " << E;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: F = b * A\n";
         F = b * A;
         cout << "RESULT: F = " << F;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: H = F + E\n";
         H = F + E;
         cout << "RESULT: G = " << G;
      }
      catch(ErrorCode e) { cout << e << endl; }

      if (G==H)
         cout << "\nOK: G==H is true\n";
      else
         cout << "\nERROR: G==H is false\n";


      //-------------------------------------------------------------
      try {
         cout << "\nACTION: G = A * B + C * D\n";
         G = A * B + C * D;
         cout << "RESULT: G = " << G;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: H = D * C + B * A\n";
         H = D * C + B * A;
         cout << "RESULT: H = " << H;
      }
      catch(ErrorCode e) { cout << e << endl; }

      if (G==H)
         cout << "\nOK: G==H is true\n";
      else
         cout << "\nERROR: G==H is false\n";


      //-------------------------------------------------------------
      try {
         cout << "\nACTION: G = A * B * C * D\n";
         G = A * B * C * D;
         cout << "RESULT: G = " << G;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: G = G / A\n";
         H = (((G / A) / D) / C);
         cout << "RESULT: G = " << H;
      }
      catch(ErrorCode e) { cout << e << endl; }

      if (B==H)
         cout << "\nOK: B==H is true\n";
      else
         cout << "\nERROR: B==H is false\n";

      //-------------------------------------------------------------
      try {
         cout << "\nACTION: G = A * B * C * D * A * B * D * C\n";
         G = A * B * C * D * A * B * D * C;
         cout << "RESULT: G = " << G;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: H = A * A * C * C * B * B * D * D\n";
         H = A * A * C * C * B * B * D * D;
         cout << "RESULT: H = " << H;
      }
      catch(ErrorCode e) { cout << e << endl; }

      if (G==H)
         cout << "\nOK: G==H is true\n";
      else
         cout << "\nERROR: G==H is false\n";

      //-------------------------------------------------------------
      try {
         cout << "\nACTION: E = (A + B) * C\n";
         E = (A + B) * C;
         cout << "RESULT: E = " << E;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: F = A * C + B * C\n";
         F = A * C + B * C;
         cout << "RESULT: F = " << F;
      }
      catch(ErrorCode e) { cout << e << endl; }

      if (E==F)
         cout << "\nOK: E==F is true\n";
      else
         cout << "\nERROR: E==F is false\n";

      //-------------------------------------------------------------
      try {
         cout << "\nACTION: E = (A + C) * (B + D)\n";
         E = (A + C) * (B + D);
         cout << "RESULT: E = " << E;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: F = B * A + D * A + C * B + D * C\n";
         F = B * A + D * A + C * B + D * C;
         cout << "RESULT: F = " << F;
      }
      catch(ErrorCode e) { cout << e << endl; }

      if (E==F)
         cout << "\nOK: E==F is true\n";
      else
         cout << "\nERROR: E==F is false\n";

      //-------------------------------------------------------------
      try {
         cout << "\nACTION: E = (A + C) / (B + D)\n";
         E = (A + C) / (B + D);
         cout << "RESULT: E = " << E;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: F = (D + B) / (C + A)\n";
         F = (D + B) / (C + A);
         cout << "RESULT: F = " << F;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: G = E * F\n";
         G = E * F;
         cout << "RESULT: G = " << G;
      }
      catch(ErrorCode e) { cout << e << endl; }


      //-------------------------------------------------------------
      try {
         cout << "\nACTION: E = (2*A + C*D) / (B*B - 5*D)\n";
         E = (2*A + C*D) / (B*B - 5*D);
         cout << "RESULT: E = " << E;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: F = ((-D)*5 + B*B) / (D*C + A*2)\n";
         F = ((-D)*5 + B*B) / (D*C + A*2);
         cout << "RESULT: F = " << F;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: G = E * F\n";
         G = E * F;
         cout << "RESULT: G = " << G;
      }
      catch(ErrorCode e) { cout << e << endl; }


      //-------------------------------------------------------------
      try {
         cout << "\nACTION: E = A / A\n";
         E = A / A;
         cout << "RESULT: E = " << E;
      }
      catch(ErrorCode e) { cout << e << endl; }

      //-------------------------------------------------------------
      try {
         cout << "\nACTION: E = GFexponentiate(A,2)\n";
         E = GFexponentiate(A,2);
         cout << "RESULT: E = " << E;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: F = A*A\n";
         F = A*A;
         cout << "RESULT: F = " << F;
      }
      catch(ErrorCode e) { cout << e << endl; }

      if (E==F)
         cout << "\nOK: E==F is true\n";
      else
         cout << "\nERROR: E==F is false\n";


      //-------------------------------------------------------------
      try {
         cout << "\nACTION: E = GFexponentiate(A,18)\n";
         E = GFexponentiate(A,18);
         cout << "RESULT: E = " << E;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: F = A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A\n";
         F = A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A;
         cout << "RESULT: F = " << F;
      }
      catch(ErrorCode e) { cout << e << endl; }

      if (E==F)
         cout << "\nOK: E==F is true\n";
      else
         cout << "\nERROR: E==F is false\n";


      //-------------------------------------------------------------
      try {
         cout << "\nACTION: E = GFexponentiate(A,137)\n";
         E = GFexponentiate(A,137);
         cout << "RESULT: E = " << E;
      }
      catch(ErrorCode e) { cout << e << endl; }

      try {
         cout << "\nACTION: F = A*A*A*A* 137 times A*A*A*A*A*A\n";
         F = A*A*A*A*A*A*A*A*A*A;
         F = F*F*F*F*F*F*F*F*F*F*F*F*F*A*A*A*A*A*A*A;

         cout << "RESULT: F = " << F;
      }
      catch(ErrorCode e) { cout << e << endl; }

      if (E==F)
         cout << "\nOK: E==F is true\n";
      else
         cout << "\nERROR: E==F is false\n";



      cout << "\n---------------------------------------------------\n";

   } // while(1)

   return 0;
}
