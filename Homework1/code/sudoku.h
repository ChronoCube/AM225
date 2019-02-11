#pragma once

#include <array>
#include <cstdint>

struct Sudoku {
    using DigitMask = unsigned int;

    int first_empty_place() const;
    DigitMask possible_digits(int);

    std::array<DigitMask, 9> masks;

    const static DigitMask ONE{static_cast<DigitMask>(1)};
    const static DigitMask TWO{static_cast<DigitMask>(1) << 1};
    const static DigitMask THREE{static_cast<DigitMask>(1) << 2};
    const static DigitMask FOUR{static_cast<DigitMask>(1) << 3};
    const static DigitMask FIVE{static_cast<DigitMask>(1) << 4};
    const static DigitMask SIX{static_cast<DigitMask>(1) << 5};
    const static DigitMask SEVEN{static_cast<DigitMask>(1) << 6};
    const static DigitMask EIGHT{static_cast<DigitMask>(1) << 7};
    const static DigitMask NINE{static_cast<DigitMask>(1) << 8};
};

bool singleton_mask(Sudoku::DigitMask dm);

