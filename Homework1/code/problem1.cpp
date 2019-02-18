#include "timer.h"
#include <fmt/format.h>
#include <iostream>
#include <random>
#include <vector>

using fmt::print;


// simulate one round at the casino
double casino(std::default_random_engine &engine,
              std::uniform_real_distribution<> &unif) {
    double sum = 0.0;
    double n = 0.0;

    // keep playing until sum exceeds 1
    while (sum < 1.0) {
        sum += unif(engine);
        n++;
    }

    return n;
}


// simulate the profit from playing NTIMES.
// The integer arguments controls the number of threads
// 
// Overall pretty straightforward, so not much to explain.
// Note that I use C++11's builtin random generation
// facilities instead of the provided code.
double simulate_profit(int nthreads = 1) {
    double sum = 0.0;
    const double NTIMES = 1000000000;

#pragma omp parallel num_threads(nthreads)
    {
        std::random_device r;
        std::default_random_engine engine(r());
        std::uniform_real_distribution<> unif(0.0, 1.0);

#pragma omp for reduction(+ : sum)
        for (int i = 0; i < (int)NTIMES; ++i) {
            sum += casino(engine, unif);
        }
    }

    double profit = 100 * sum / NTIMES - 250;
    return profit;
}

int main(int argc, char **argv) {
    std::vector<int> nthreads = {1, 2, 4, 12};
    print("{}\t{}\t{}\n", "threads", "time", "profit");

    for (auto &&n : nthreads) {
        Timer t;
        double profit = simulate_profit(n);
        double elapsed = t.elapsed();

        print("{}\t{}\t{}\n", n, elapsed, profit);
    }

    return 0;
}
