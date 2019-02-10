#include <cstdint>
#include <vector>
#include <numeric>

using std::vector;
using Digit = uint64_t;
using Digits = std::vector<Digit>;

std::pair<Digits, uint64_t> long_division(Digits digits, uint64_t base,
                                          uint64_t divisor) {
    Digits quotient;

    auto n = digits.size();
    Digits::size_type index = 0; // place of the leading digit

    while (index < n - 1 || (index == n - 1 && digits[index] >= divisor)) {
        uint64_t current_digit = digits[index];

        if (current_digit >= divisor) {
            uint64_t q = current_digit / divisor;
            uint64_t r = current_digit - q * divisor;
            quotient.push_back(q);

            if (r > 0) {
                digits[index] = r;
            } else {
                index++;
            }
        } else {
            uint64_t current_number = current_digit * base + digits[index + 1];
            uint64_t q = current_number / divisor;
            uint64_t r = current_number - q * divisor;
            quotient.push_back(q);

            if (r > 0) {
                index += 1;
                digits[index] = r;
                if (index == n - 1) {
                    return {quotient, r};
                }
            } else {
                index += 2;
            }
        }
    }

    uint64_t remainder = 0;
    // We typically exit because index == n - 1, but
    // occasionally, it may be possible that index = n,
    // which occurs when there's a carry in the last round
    // and divisor perfect divides the carry.
    if (index == n - 1) {
        quotient.push_back(0);
        remainder = digits[n - 1];
    }

    return {quotient, remainder};
}

std::vector<uint64_t> generate_primes(uint64_t upper_bound) {
    // increment to compensate for starting at index 0;
    upper_bound += 1;

    vector<int> is_prime(upper_bound, 1);

    is_prime[0] = 0;
    is_prime[1] = 0;

    for (uint64_t i = 2; i * i <= upper_bound; i++) {
        if (is_prime[i]) {
#pragma omp parallel for
            for (uint64_t j = i * i; j < upper_bound; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    uint64_t prime_count =
        std::accumulate(std::begin(is_prime), std::end(is_prime), 0);

    vector<uint64_t> primes(prime_count);
    for (uint64_t i = 0, k = 0; i < upper_bound; i++) {
        if (is_prime[i])
            primes[k++] = i;
    }

    return primes;
}
