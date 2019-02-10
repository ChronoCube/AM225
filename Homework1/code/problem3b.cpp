#include "cleantype/cleantype.hpp"
#include "fmt/format.h"
#include "problem3.h"
#include <cstdint>
#include <vector>

using fmt::print;

using Digit = uint64_t;
using Digits = std::vector<Digit>;

int main(int argc, char **argv) {
    uint64_t base = 10;
    uint64_t divisor = 9;

    Digits digits = {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,1};

    auto result = long_division(digits, base, divisor);
    print("{}\n", CT_show_details(result));
    return 0;
}
