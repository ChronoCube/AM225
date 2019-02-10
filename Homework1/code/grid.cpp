#include "grid.h"
#include "omp.h"
#include <cstring>
#include <iostream>
#include <random>
#include <utility>

Grid::Grid(int m_, int n_) : m(m_), n(n_), grid(new int[m * n]) {
    for (int x = 0; x < m * n; x++) {
        grid[x] = 0;
    }

    std::random_device r;
    std::default_random_engine engine(r());
    std::bernoulli_distribution bernoulli(0.75);

    for (int i = m / 2 - 6; i <= m / 2 + 6; i++) {
        for (int j = n / 2 - 6; j <= n / 2 + 6; j++) {
            operator()(i, j) = bernoulli(engine);
        }
    }
}

Grid::Grid(const Grid &other) : m(other.m), n(other.n), grid(new int[m * n]) {
    std::memcpy(grid, other.grid, sizeof(int) * m * n);
}

Grid &Grid::operator=(Grid other) {
    m = other.m;
    n = other.n;

    using std::swap;

    swap(grid, other.grid);
    return *this;
}

Grid::~Grid() { delete[] grid; }

int Grid::neighbors(int i, int j) const {
    int count = -operator()(i, j);

    int x_low = (i == 0) ? 0 : -1;
    int x_high = (i == m - 1) ? 0 : 1;

    int y_low = (j == 0) ? 0 : -1;
    int y_high = (j == n - 1) ? 0 : 1;

    for (int x = x_low; x <= x_high; x++) {
        for (int y = y_low; y <= y_high; y++) {
            count += operator()(i + x, j + y);
        }
    }
    return count;
}

const int &Grid::operator()(int i, int j) const {
    if (i < 0) {
        i = m + i;
    } else if (i >= m) {
        i = i - m;
    }
    if (j < 0) {
        j = n + j;
    } else if (j >= n) {
        j = j - n;
    }
    return grid[n * i + j];
}
int &Grid::operator()(int i, int j) {
    if (i < 0) {
        i = m + i;
    } else if (i >= m) {
        i = i - m;
    }
    if (j < 0) {
        j = n + j;
    } else if (j >= n) {
        j = j - n;
    }
    return grid[n * i + j];
}

Grid evolve(const Grid &grid, int nthreads = 0) {
    Grid next(grid.m, grid.n);

    if (nthreads == 0)
        nthreads = omp_get_num_threads();

#pragma omp parallel for collapse(2) num_threads(nthreads)
    for (int i = 0; i < grid.m; i++) {
        for (int j = 0; j < grid.n; j++) {
            int n = grid.neighbors(i, j);

            if (grid(i, j))
                next(i, j) = (1 <= n && n <= 5);
            else
                next(i, j) = (n == 3);
        }
    }
    return next;
}

void print_grid(const Grid &grid) {
    for (int i = 0; i < grid.m; i++) {
        for (int j = 0; j < grid.n; j++) {
            if (grid(i, j))
                std::cout << "█";
            else
                std::cout << ' ';
        }
        std::cout << '\n';
    }
    return;
}

int sum_grid(const Grid &grid) {
    int count = 0;
    for (int i = 0; i < grid.m; i++) {
        for (int j = 0; j < grid.n; j++) {
            count += grid(i, j);
        }
    }
    return count;
}
