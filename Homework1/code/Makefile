CXX=g++
CFLAGS=-std=c++14 -fopenmp -O2 -march=native -Wall -Wpedantic -g
INC=-Iinclude

COMMON_HEADERS=timer.h
COMMON_OBJS=format.o


all : one two-a two-b

two-b : problem2b.cpp grid.h grid.o $(COMMON_HEADERS) $(COMMON_OBJS)
	$(CXX) $(CFLAGS) $(INC) problem2b.cpp grid.o $(COMMON_OBJS) -o two-b

two-a : problem2a.cpp grid.h grid.o $(COMMON_HEADERS) $(COMMON_OBJS)
	$(CXX) $(CFLAGS) $(INC) problem2a.cpp grid.o $(COMMON_OBJS) -o two-a

one : problem1.cpp $(COMMON_HEADERS) $(COMMON_OBJS)
	$(CXX) $(CFLAGS) $(INC) $(COMMON_OBJS) problem1.cpp -o one

format.o : format.cc
	$(CXX) $(INC) -std=c++14 -O2 -march=native -c format.cc

grid.o : grid.cpp grid.h
	$(CXX) $(CFLAGS) $(INC) -c grid.cpp -o grid.o

clean:
	rm -f one two-a two-b grid.o $(COMMON_OBJS)
