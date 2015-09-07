#**********************************************************************
#
#       Project: C++ Library for General Galois Field Arithmetic
#
#   Author: Saied H. Khayat
#   Email:  shk@alum.wustl.edu
#   Date:   February 2013
#
#   Copyright Notice: Free use of this library is permitted under the
#   guidelines and in accordance with the MIT License (MIT).
#   http://opensource.org/licenses/MIT
#
#**********************************************************************

# GNU Makefile to build the "test_gfelement" executable

CC     = g++
CFLAGS = -pedantic -ansi -Wall -O3 -o
LFLAGS = -pedantic -ansi -Wall -O3 -c
OBJS   = gfelement.o  galoisfield.o  polynomial_arith.o  modular_arith.o

test_gfelement: test_gfelement.cpp $(OBJS)
	$(CC) $(CFLAGS) test_gfelement test_gfelement.cpp $(OBJS)

gfelement.o: gfelement.h gfelement.cpp typedefs.h
	$(CC) $(LFLAGS) gfelement.cpp

galoisfield.o: galoisfield.h galoisfield.cpp typedefs.h
	$(CC) $(LFLAGS) galoisfield.cpp

polynomial_arith.o: polynomial_arith.h  polynomial_arith.cpp  modular_arith.h typedefs.h
	$(CC) $(LFLAGS) polynomial_arith.cpp

modular_arith.o: modular_arith.h  modular_arith.cpp  typedefs.h
	$(CC) $(LFLAGS) modular_arith.cpp

clean:
	/bin/rm -f *.o

