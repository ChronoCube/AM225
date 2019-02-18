#include <cstdint>
#include <vector>
#include <numeric>

using std::vector;
using Digit = uint64_t;
using Digits = std::vector<Digit>;



// the long division algorithm.
// Takes in a vector of digits (each digit is a uint64),
// with the leading digit first, e.g. 100 is {1, 0, 0} in base 10.
//
// The base specifies the base to interpret the digit in,
// and the divisor is assumed to be less than the base.
//
// Returns a pair where the first member is the quotient (vector of digits),
// and a remainder.
std::pair<Digits, uint64_t> long_division(Digits digits, uint64_t base,
                                          uint64_t divisor) {
    Digits quotient;

    auto n = digits.size();

    // Index will always be the index of the leading digit
    // of the dividend. We advance it everytime we succesfully
    // divide. We finish when index runs past digits
    // or the last digit is less than the divisor (in which case that is remainder).
    Digits::size_type index = 0;

    while (index < n - 1 || (index == n - 1 && digits[index] >= divisor)) {
        uint64_t current_digit = digits[index];

        if (current_digit >= divisor) {
            // no carry needed.
            uint64_t q = current_digit / divisor;
            uint64_t r = current_digit - q * divisor;
            quotient.push_back(q);

            if (r > 0) {
                digits[index] = r;
            } else {
                index++;
            }
        } else {
            // we need to carry
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


// Standard sieve of Eratosthenes. Returns a vector
// of primes.
std::vector<uint64_t> generate_primes(uint64_t upper_bound) {
    // increment to compensate for starting at index 0;
    upper_bound += 1;

    // is_prime[i] is non-zero if i is prime.
    vector<int> is_prime(upper_bound, 1);

    is_prime[0] = 0;
    is_prime[1] = 0;


    // we only need to go up to the square root
    // in checking for factors
    for (uint64_t i = 2; i * i <= upper_bound; i++) {
        if (is_prime[i]) {
#pragma omp parallel for
            // j < i * i would have been marked in a previous iteration.
            for (uint64_t j = i * i; j < upper_bound; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    uint64_t prime_count =
        std::accumulate(std::begin(is_prime), std::end(is_prime), 0);

    // collect the primes and return it.
    vector<uint64_t> primes(prime_count);
    for (uint64_t i = 0, k = 0; i < upper_bound; i++) {
        if (is_prime[i])
            primes[k++] = i;
    }

    return primes;
}
