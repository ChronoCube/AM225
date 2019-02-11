#include "sudoku.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    Sudoku::DigitMask x = Sudoku::FOUR;
    cout << singleton_mask(x) << endl;
    return 0;
}

