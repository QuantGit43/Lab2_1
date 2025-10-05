#include "BoardCellPicker.h"
#include <chrono>

BoardCellPicker::BoardCellPicker(int board_size) : N(board_size) {
    if (N <= 0) {
        throw InputError("Розмір дошки N має бути додатним.");
    }

    std::random_device rd;
    engine.seed(rd() ^ std::chrono::high_resolution_clock::now().time_since_epoch().count());

    dist = std::uniform_int_distribution<int>(0, N - 1);
}

Cell BoardCellPicker::operator()() {
    int row = dist(engine);
    int col = dist(engine);
    return { row, col };
}