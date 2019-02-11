#include "sudoku.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

namespace chronocube {
namespace sudoku {

Sudoku from_array(std::array<int, 81> input) {
    Sudoku sudoku;

    for (std::size_t i = 0; i < 81; i++) {
        sudoku[i] = BLANK;
    }

    for (std::size_t i = 0; i < 81; i++) {
        if (input[i])
            sudoku =
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

DigitMask single_digit(std::size_t shift) {
    DigitMask mask(1);
    return mask << shift;
}

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

#include "sudoku_const.data"

bool singleton_mask(const DigitMask &dm) { return dm.count() == 1; }

int first_empty_place(const Sudoku &s) {
    for (int i = 0; i < 81; i++) {
        if (s[i].count() >= 2)
            return i;
    }
    return 999;
}

bool completed(const Sudoku &s) { return first_empty_place(s) == 999; }

bool coherent(const Sudoku &s) {
    for (auto &&x : s) {
        if (x.none())
            return false;
    }

    for (std::size_t n = 0; n < 81; n++) {
        for (std::size_t d = 0; d < 9; d++) {
            if (s[n].count() == 1) {
                for (auto &&cell : ASSOCIATIONS[n]) {
                    if (s[cell] == s[n])
                        return false;
                }
            }
        }
    }

    return true;
}

std::vector<DigitMask> possible_digits(const DigitMask &mask) {
    std::vector<DigitMask> possibilities;

    for (auto i = 0; i < 9; i++) {
        if (mask[i]) {
            possibilities.push_back(single_digit(i));
        }
    }
    return possibilities;
}

Sudoku fill_in(Sudoku s, int n, const DigitMask &mask) {
    s[n] = mask;

    for (auto &&i : ASSOCIATIONS[n]) {
        s[i] = s[i] & (~mask);
    }

    return s;
}

std::vector<Sudoku> solve(const Sudoku &sudoku) {
    if (sudoku::coherent(sudoku) == false)
        return {};

    if (sudoku::completed(sudoku)) {
        return {sudoku};
    }

    int slot = sudoku::first_empty_place(sudoku);

    std::vector<Sudoku> solutions = {};
    for (auto &&possibility : sudoku::possible_digits(sudoku[slot])) {
        auto s = sudoku::fill_in(sudoku, slot, possibility);
        for (auto &&solution : solve(s)) {
            solutions.push_back(solution);
        }
    }
    return solutions;
}

} // namespace sudoku
} // namespace chronocube
