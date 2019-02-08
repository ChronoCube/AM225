CXX=g++
CFLAGS=-std=c++14 -fopenmp -O2 -march=native -Wall -Wpedantic -g

COMMON_HEADERS=timer.h


all : one two
two : problem2.cpp problem2a.cpp problem2b.cpp $(COMMON_HEADERS)
	$(CXX) $(CFLAGS) problem2.cpp -o two

one : problem1.cpp $(COMMON_HEADERS)
	$(CXX) $(CFLAGS) problem1.cpp -o one
