CXX=g++
CFLAGS=-std=c++14 -fopenmp -O2 -march=native -Wall -Wpedantic -g

COMMON_HEADERS=timer.h


all : one two-a two-b

two-b : problem2b.cpp grid.h grid.o $(COMMON_HEADERS)
	$(CXX) $(CFLAGS) problem2b.cpp grid.o -o two-b

two-a : problem2a.cpp grid.h grid.o $(COMMON_HEADERS)
	$(CXX) $(CFLAGS) problem2a.cpp grid.o -o two-a

grid.o : grid.cpp grid.h
	$(CXX) $(CFLAGS) -c grid.cpp -o grid.o

one : problem1.cpp $(COMMON_HEADERS)
	$(CXX) $(CFLAGS) problem1.cpp -o one

clean:
	rm -f one two-a two-b grid.o
