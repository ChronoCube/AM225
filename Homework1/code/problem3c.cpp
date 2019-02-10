#include "fmt/format.h"
#include "problem3.h"
#include <cstdint>
#include <vector>

using fmt::print;
using Digit = uint64_t;
using Digits = std::vector<Digit>;

int main(int argc, char **argv) {
    const uint64_t base_repr = static_cast<uint64_t>(32);
    const uint64_t base = static_cast<uint64_t>(1) << base_repr;

    const uint64_t mersenne_exponent = 82589933;
    const auto ndigits = mersenne_exponent / base_repr + 1;

    Digits d;
    for (uint64_t i = 0; i < ndigits; i++) {
        if (i == 0) {
            d.push_back(
                (static_cast<uint64_t>(1) << (mersenne_exponent % base_repr)) -
                1);
        } else {
            d.push_back(base - 1);
        }
    }

    auto primes = generate_primes(200000);
    auto n = primes.size();

#pragma omp parallel for
    for (uint64_t i = 0; i < n; i++) {
        auto p = primes[i];
        auto result = long_division(d, base, p);

        if (result.second == 0) {
            print("@{}\n", p);
        } else {
            print("{}\n", p);
        }
    }

    return 0;
}
