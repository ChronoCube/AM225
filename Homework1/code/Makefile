CXX=g++
CFLAGS=-std=c++14 -fopenmp -O2 -march=native -Wall -Wpedantic -g
INC=-I../../common/include

COMMON_HEADERS=timer.h ../../common/include/cleantype/cleantype.hpp
COMMON_OBJS=format.o

EXE=one.bin two-a.bin two-b.bin three-a.bin three-b.bin three-c.bin three-d.bin four-a.bin four-b.bin four-c.bin


all : $(EXE)

four-c.bin : problem4c.cpp sudoku.o $(COMMON_HEADERS) $(COMMON_OBJS)
	$(CXX) $(CFLAGS) $(INC) problem4c.cpp sudoku.o $(COMMON_OBJS) -o four-c.bin

four-b.bin : problem4b.cpp sudoku.o $(COMMON_HEADERS) $(COMMON_OBJS)
	$(CXX) $(CFLAGS) $(INC) problem4b.cpp sudoku.o $(COMMON_OBJS) -o four-b.bin

four-a.bin : problem4a.cpp sudoku.o $(COMMON_HEADERS) $(COMMON_OBJS)
	$(CXX) $(CFLAGS) $(INC) problem4a.cpp sudoku.o $(COMMON_OBJS) -o four-a.bin

three-d.bin : problem3d.cpp $(COMMON_HEADERS) $(COMMON_OBJS) problem3.o
	$(CXX) $(CFLAGS) $(INC) problem3d.cpp problem3.o $(COMMON_OBJS) -o three-d.bin

three-c.bin : problem3c.cpp $(COMMON_HEADERS) $(COMMON_OBJS) problem3.o
	$(CXX) $(CFLAGS) $(INC) problem3c.cpp problem3.o $(COMMON_OBJS) -o three-c.bin

three-b.bin : problem3b.cpp $(COMMON_HEADERS) $(COMMON_OBJS) problem3.o
	$(CXX) $(CFLAGS) $(INC) problem3b.cpp problem3.o $(COMMON_OBJS) -o three-b.bin

three-a.bin : problem3a.cpp $(COMMON_HEADERS) $(COMMON_OBJS) problem3.o
	$(CXX) $(CFLAGS) $(INC) problem3a.cpp problem3.o $(COMMON_OBJS) -o three-a.bin

two-b.bin : problem2b.cpp grid.h grid.o $(COMMON_HEADERS) $(COMMON_OBJS)
	$(CXX) $(CFLAGS) $(INC) problem2b.cpp grid.o $(COMMON_OBJS) -o two-b.bin

two-a.bin : problem2a.cpp grid.h grid.o $(COMMON_HEADERS) $(COMMON_OBJS)
	$(CXX) $(CFLAGS) $(INC) problem2a.cpp grid.o $(COMMON_OBJS) -o two-a.bin

one.bin : problem1.cpp $(COMMON_HEADERS) $(COMMON_OBJS)
	$(CXX) $(CFLAGS) $(INC) $(COMMON_OBJS) problem1.cpp -o one.bin

problem3.o : problem3.cpp problem3.h
	$(CXX) $(INC) -std=c++14 -O2 -march=native -c problem3.cpp -o problem3.o

format.o : ../../common/format.cc
	$(CXX) $(INC) -std=c++14 -O2 -march=native -c ../../common/format.cc -o format.o

sudoku.o : sudoku.cpp sudoku.h
	$(CXX) $(CFLAGS) $(INC) -c sudoku.cpp -o sudoku.o

grid.o : grid.cpp grid.h
	$(CXX) $(CFLAGS) $(INC) -c grid.cpp -o grid.o

clean:
	rm -f $(EXE) grid.o $(COMMON_OBJS) problem3.o
