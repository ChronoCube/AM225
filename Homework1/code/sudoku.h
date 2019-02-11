#pragma once

#include <array>
#include <bitset>
#include <cstdint>
#include <vector>

namespace chronocube {
namespace sudoku {
using DigitMask = std::bitset<9>;
using Sudoku = std::array<DigitMask, 81>;

Sudoku from_array(std::array<int, 81> array);
void print_sudoku(const Sudoku &s);

DigitMask single_digit(std::size_t shift);
char mask_to_integer(const sudoku::DigitMask &dm);

const DigitMask ONE = single_digit(0);
const DigitMask TWO = single_digit(1);
const DigitMask THREE = single_digit(2);
const DigitMask FOUR = single_digit(3);
const DigitMask FIVE = single_digit(4);
const DigitMask SIX = single_digit(5);
const DigitMask SEVEN = single_digit(6);
const DigitMask EIGHT = single_digit(7);
const DigitMask NINE = single_digit(8);
const DigitMask BLANK =
    ONE | TWO | THREE | FOUR | FIVE | SIX | SEVEN | EIGHT | NINE;

int first_empty_place(const Sudoku &s);
bool completed(const Sudoku &s);
bool coherent(const Sudoku &s);
bool singleton_mask(const DigitMask &dm);
std::vector<DigitMask> possible_digits(const DigitMask &mask);
Sudoku fill_in(Sudoku s, int n, const DigitMask &mask);

std::vector<Sudoku> solve(const Sudoku &sudoku);
} // namespace sudoku
} // namespace chronocube
