#include "sudoku.h"
#include <fmt/format.h>

using fmt::print;

namespace sudoku = chronocube::sudoku;
using sudoku::from_array;
using sudoku::print_sudoku;
using sudoku::Sudoku;

int main(int argc, char **argv) {
    // clang-format off
    std::array<int, 81> input = {{
        1, 2, 3, 0, 0, 0, 0, 0, 0,
        4, 5, 6, 0, 0, 0, 0, 0, 0,
        7, 8, 9, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 2, 3, 0, 0, 0,
        0, 0, 0, 4, 5, 6, 0, 0, 0,
        0, 0, 0, 7, 8, 9, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 2, 3,
        0, 0, 0, 0, 0, 0, 4, 5, 6,
        0, 0, 0, 0, 0, 0, 7, 8, 9
    }};
    // clang-format on

    auto puzzle = from_array(input);
    auto solutions = sudoku::solve(puzzle);

    print("Number of solutions: {}. ", solutions.size());
    print("Here is one of them:\n", solutions.size());
    print_sudoku(solutions[0]);

    return 0;
}

