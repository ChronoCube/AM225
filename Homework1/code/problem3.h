#pragma once

#include <cstdint>
#include <utility>
#include <vector>

std::pair<std::vector<uint64_t>, uint64_t>
long_division(std::vector<uint64_t> digits, uint64_t base, uint64_t divisor);

std::vector<uint64_t> generate_primes(uint64_t upper_bound);
