#include "sudoku.h"
#include "timer.h"
#include <fmt/format.h>
#include <vector>

using fmt::print;

namespace sudoku = chronocube::sudoku;
using sudoku::from_array;
using sudoku::print_sudoku;
using sudoku::Sudoku;

int main(int argc, char **argv) {
    // clang-format off
    std::array<int, 81> input = {{
        1, 0, 0, 9, 0, 7, 0, 0, 3,
        0, 8, 0, 0, 0, 0, 0, 7, 0,
        0, 0, 9, 0, 0, 0, 6, 0, 0,
        0, 0, 7, 2, 0, 9, 4, 0, 0,
        4, 1, 0, 0, 0, 0, 0, 9, 5, 
        0, 0, 8, 5, 0, 4, 3, 0, 0,
        0, 0, 3, 0, 0, 0, 7, 0, 0,
        0, 5, 0, 0, 0, 0, 0, 4, 0,
        2, 0, 0, 8, 0, 6, 0, 0, 9
    }};
    // clang-format on
    auto puzzle = from_array(input);
    int ntimes = 1000;

    Timer t;
    for (int i = 0; i < ntimes; i++) {
        auto solutions = sudoku::solve(puzzle);
    }
    print("Time (milliseconds) to repeat {} times: {}.\n", ntimes, t.elapsed());
    print("per time = {}\n", t.elapsed()/ntimes);

    auto solutions = sudoku::solve(puzzle);
    print("Number of solutions: {}. ", solutions.size());
    print("Here is one of them:\n", solutions.size());
    print_sudoku(solutions[0]);

    return 0;
}

