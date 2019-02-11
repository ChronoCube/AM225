#include "sudoku.h"

bool singleton_mask(Sudoku::DigitMask dm) {
    return __builtin_popcount(dm) == 1;
}


int Sudoku::first_empty_place() const {
    for (int i = 0; i < 9; i++) {
        if (singleton_mask(masks[i])) {
            return i;
        }
    }
    return 10;
}
