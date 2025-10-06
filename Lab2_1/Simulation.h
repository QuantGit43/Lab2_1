#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include "CellPicker.h"

struct Result {
    double mean_size = 0.0;
    double median_size = 0.0;
};

class BoardSimulation {
private:
    const int N;
    const int K;

    void mark_cell_and_neighbours(std::vector<std::vector<bool>>& board, int r, int c);
    long long single_simulation(BoardCellPicker& picker);

public:
    BoardSimulation(int board_size, int num_picks);

    Result multiple_simulations(int num_simulations);
};