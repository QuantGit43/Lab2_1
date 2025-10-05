#pragma once
#include <random>
#include "Utilities.h"

class BoardCellPicker {
private:
    std::mt19937 engine;
    std::uniform_int_distribution<int> dist;
    const int N; 
public:
    BoardCellPicker(int board_size);

    Cell operator()();

    int get_board_size() const { return N; }
};