#include <algorithm>
#include <fmt/format.h>
#include <numeric>
#include <vector>

#include "problem3.h"

using fmt::print;
using std::vector;

int main(int argc, char **argv) {
    auto primes = generate_primes(2 * 100000);
    for (auto &&x : primes) {
        print("{}\n", x);
    }
    return 0;
}
