#include "grid.h"
#include "timer.h"
#include <iostream>

using std::cout;

int main(int argc, char **argv) {
    std::vector<int> sizes = {16, 32, 64, 128, 256, 512, 1024};
    std::vector<int> nthreads = {1, 2, 3, 4};

    cout << "n" << '\t' << "T" << '\t' << "w" << '\n';
    for (auto &&n : sizes) {
        for (auto &&t : nthreads) {
            Grid grid(n, n);

            Timer timer;

            for (int x = 0; x < (n < 512 ? 500 : 250); x++)
                grid = evolve(grid, t);

            cout << n << '\t' << t << '\t' << timer.elapsed() / 100 << '\n';
        }
    }

    return 0;
}

