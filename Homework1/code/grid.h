#pragma once


#include <iostream>
#include <utility>
#include <random>
#include <cstring>

struct Grid {
    int m;
    int n;
    int *grid;

    Grid(int m_, int n_);

    Grid(const Grid &other);

    Grid& operator=(Grid other);

    ~Grid();
    int neighbors(int i, int j) const;
    const int &operator()(int i, int j) const;
    int &operator()(int i, int j);
};

Grid evolve(const Grid &grid, int nthreads);
void print_grid(const Grid &grid);
int sum_grid(const Grid &grid);
