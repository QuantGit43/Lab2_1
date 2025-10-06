#pragma once
#include <random>
#include <string>

struct Cell {
    int row;
    int col;

    std::string to_string() const {
        return "(" + std::to_string(row) + ", " + std::to_string(col) + ")";
    }
};

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