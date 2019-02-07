CXX=g++
CFLAGS=-fopenmp -O2 -march=native


one : problem1.cpp
	$(CXX) $(CFLAGS) problem1.cpp -o one
