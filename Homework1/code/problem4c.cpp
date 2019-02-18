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
        1, 0, 0, 0, 0, 0, 0, 0, 2,
        0, 5, 0, 0, 0, 0, 0, 4, 0,
        0, 0, 9, 0, 0, 0, 6, 0, 0,
        0, 0, 0, 1, 0, 2, 0, 0, 0,
        0, 0, 0, 0, 8, 0, 0, 0, 0,
        0, 0, 0, 6, 0, 9, 0, 0, 0,
        0, 0, 2, 0, 0, 0, 1, 0, 0,
        0, 4, 0, 0, 0, 0, 0, 5, 0,
        6, 0, 0, 0, 0, 0, 0, 0, 9
    }};
    // clang-format on

    auto puzzle = from_array(input);
    print_sudoku(puzzle);
    print("\n");

    auto count = sudoku::count_solutions_parallel(puzzle, 1);
    print("Number of solutions: {}.\n", count);


    return 0;
}

