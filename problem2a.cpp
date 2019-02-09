#include "grid.h"
#include "timer.h"
#include <iostream>

using std::cout;

int main(int argc, char **argv) {
    int m = 80;
    int n = 40;

    int generation = 0;
    Grid g(m, n);

    do {
        if (generation % 25 == 0) {
            print_grid(g);
            cout << "\n\n\n";
        }

        g = evolve(g, 2);
        generation++;
    } while (generation <= 150);

    return 0;
}
