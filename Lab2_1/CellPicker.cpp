#include "CellPicker.h"

BoardCellPicker::BoardCellPicker(int board_size) : N(board_size) {
    if (N <= 0) {
        throw std::invalid_argument("N must be > 0, K must be >= 0.");
    }
    std::random_device rd;


    std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };

    engine.seed(ss);

    dist = std::uniform_int_distribution<int>(0, N - 1);
}

Cell BoardCellPicker::operator()() {
    int row = dist(engine);
    int col = dist(engine);
    return { row, col };
}