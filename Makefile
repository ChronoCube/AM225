CXX=g++
CFLAGS=-std=c++14 -fopenmp -O2 -march=native -Wall -Wpedantic -g

all : one two
two : problem2.cpp
	$(CXX) $(CFLAGS) problem2.cpp -o two

one : problem1.cpp
	$(CXX) $(CFLAGS) problem1.cpp -o one
