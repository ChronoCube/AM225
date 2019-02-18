#include "sudoku.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;



// A sudoku board is represented as 81 bitmasks. Each bitmask has 9 bits,
// where the bit i is equal to '1' if i is not-disallowed
// at that square.

namespace chronocube {
namespace sudoku {

// this keeps some constant data related to sudoku,
// namely, ASSOCIATION[i] is the set of all indices
// which belong to the same row, column, or 3x3 cell
// as index i. I wrote a Python program (not included)
// to generate this data.
#include "sudoku_const.data"

// convenience function to construct a sudoku puzzle
// from an array. See problem4a.cpp to see how this is used.
Sudoku from_array(std::array<int, 81> input) {
    Sudoku sudoku;

    for (std::size_t i = 0; i < 81; i++) {
        sudoku[i] = BLANK;
    }

    for (std::size_t i = 0; i < 81; i++) {
        if (input[i])
            sudoku::fill_in(sudoku, i, sudoku::single_digit(input[i] - 1));
    }

    return sudoku;
}

void print_sudoku(const Sudoku &s) {
    cout << "┏━━━━━━━┳━━━━━━━┳━━━━━━━┓" << '\n';
    for (size_t i = 0; i < 9; i++) {
        if (i == 3 || i == 6)
            cout << "┣━━━━━━━╋━━━━━━━╋━━━━━━━┫" << '\n';

        for (size_t j = 0; j < 9; j++) {
            if (j == 0 || j == 3 || j == 6)
                cout << "┃ ";
            cout << mask_to_integer(s[9 * i + j]) << " ";
        }
        cout << "┃" << '\n';
    }

    cout << "┗━━━━━━━┻━━━━━━━┻━━━━━━━┛" << '\n';
    return;
}


// generate bit mask that is equal a square that is filled in,
// i.e. only one possibility is allowed.
//
// See header file to see how this is used to define constants.
DigitMask single_digit(std::size_t shift) {
    DigitMask mask(1);
    return mask << shift;
}

// the constants ONE, TWO, ..., NINE are
// defined in the header file. This function
// is just used for pretty printing.
char mask_to_integer(const sudoku::DigitMask &dm) {
    if (dm == ONE)
        return '1';
    if (dm == TWO)
        return '2';
    if (dm == THREE)
        return '3';
    if (dm == FOUR)
        return '4';
    if (dm == FIVE)
        return '5';
    if (dm == SIX)
        return '6';
    if (dm == SEVEN)
        return '7';
    if (dm == EIGHT)
        return '8';
    if (dm == NINE)
        return '9';

    return '0';
}

// true if the bitmask only contains a single possible square.
bool is_singleton(const DigitMask &dm) { return dm.count() == 1; }


// find the first place in the Sudoku board where
// there is more than one possibility.
int first_empty_place(const Sudoku &s) {
    for (int i = 0; i < 81; i++) {
        if (s[i].count() >= 2)
            return i;
    }
    return 999;
}

bool completed(const Sudoku &s) { return first_empty_place(s) == 999; }


// See the write up PDF.  everytime place is filled in,
// this function goes and eliminates cells in the 
// same row, column, or 3x3 square as place.  If, in this process,
// any cell becomes filled in (i.e., because there is only one possibility),
// then we reduce again at that cell. 
//
// Returns *FALSE* if this leads to a invalid puzzle, i.e., if some
// square during this process has NO legal possibilities.
//
// Returns *TRUE* otherwise
bool reduce_at(Sudoku &s, int place) {
    auto mask = s[place];

    for (auto &&k : ASSOCIATIONS[place]) {
        auto c = s[k].count();
        s[k] = s[k] & (~mask);
        auto d = s[k].count();

        if (d == 0)
            return false;

        if (c != d && d == 1) {
            auto valid = reduce_at(s, k);
            if (valid == false)
                return false;
        }
    }

    return true;
}


// Returns single-digit bit masks corresponding
// to the legal squares of the mask. E.g., 
// 100100100 returns {NINE, SIX, THREE}
std::vector<DigitMask> possible_digits(const DigitMask &mask) {
    std::vector<DigitMask> possibilities;

    for (auto i = 0; i < 9; i++) {
        if (mask[i]) {
            possibilities.push_back(single_digit(i));
        }
    }
    return possibilities;
}


// fills in a square, and reduces at that square (see the documentation
// for reduce_at)
bool fill_in(Sudoku &s, int n, const DigitMask &mask) {
    s[n] = mask;
    return reduce_at(s, n);
}

// Modulo, bookkeeping differences, this is essentially Algorithm 1
// in the problem text. (this just counts solutions, not
// stores them. See the function solve)
int count_solutions(const Sudoku &sudoku) {
    if (sudoku::completed(sudoku)) {
        return 1;
    }

    int slot = sudoku::first_empty_place(sudoku);

    int count = 0;
    for (auto &&possibility : sudoku::possible_digits(sudoku[slot])) {
        Sudoku copy = sudoku;
        auto valid = sudoku::fill_in(copy, slot, possibility);
        if (valid)
            count += count_solutions(copy);
    }
    return count;
}


// count the solutions in parallel. We bail out 
// to the single threaded version if there aren't that
// many cells left. (The best number was done by trial and error...)
//
//
// Modulo, bookkeeping differences, this is essentially Algorithm 1
// in the problem text.
int count_solutions_parallel(const Sudoku &sudoku, int nthreads = 1) {
    if (sudoku::completed(sudoku)) {
        return 1;
    }

    const int slot = sudoku::first_empty_place(sudoku);

    // fast bail-out if we're close to the end
    if (slot >= 75)
        return count_solutions(sudoku);

    int count = 0;
    auto possibilities = possible_digits(sudoku[slot]);
    auto n = possibilities.size();

#pragma omp parallel for reduction(+ : count) num_threads(nthreads)
    for (std::size_t i = 0; i < n; i++) {
        Sudoku copy = sudoku;
        auto valid = sudoku::fill_in(copy, slot, possibilities[i]);
        if (valid)
            count += count_solutions(copy);
    }

    return count;
}


// finds *All* solutions to a given puzzle. (not merely count them,
// the logic is very similar to counting).
std::vector<Sudoku> solve(const Sudoku &sudoku) {
    if (sudoku::completed(sudoku)) {
        return {sudoku};
    }

    int slot = sudoku::first_empty_place(sudoku);

    std::vector<Sudoku> solutions = {};
    for (auto &&possibility : sudoku::possible_digits(sudoku[slot])) {
        Sudoku copy = sudoku;
        auto valid = sudoku::fill_in(copy, slot, possibility);
        if (valid) {
            for (auto &&solution : solve(copy)) {
                solutions.push_back(solution);
            }
        }
    }
    return solutions;
}

} // namespace sudoku
} // namespace chronocube
