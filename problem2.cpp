#include <array>
#include <cstring>
#include <iostream>
#include <random>
#include <utility>

using std::cout;


struct Grid {
  int m;
  int n;
  int *grid;

  Grid(int m_, int n_) : m(m_), n(n_), grid(new int[m * n]) {
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

  Grid(const Grid &other) : m(other.m), n(other.n), grid(new int[m * n]) {
    memcpy(grid, other.grid, sizeof(int) * m * n);
  }

  Grid &operator=(Grid other) {
    m = other.m;
    n = other.n;
    std::swap(grid, other.grid);
    return *this;
  }

  ~Grid() { delete[] grid; }

  int neighbors(int i, int j) const {
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

  const int &operator()(int i, int j) const { return grid[n * i + j]; }

  int &operator()(int i, int j) { return grid[n * i + j]; }

  int sum() const {
    int count = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        count += operator()(i, j);
      }
    }
    return count;
  }
};

Grid evolve(const Grid &grid) {
  Grid next(grid.m, grid.n);
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

int main(int argc, char **argv) {
  int M = 80;
  int N = 40;

  Grid grid(M, N);

  Grid newgrid = evolve(grid);
  cout << grid.sum() << '\n';
  cout << newgrid.sum() << '\n';
  return 0;
}
