#include "Simulation.h"
#include <numeric>
#include <algorithm>
#include <cmath>

BoardSimulation::BoardSimulation(int board_size, int num_picks) : N(board_size), K(num_picks) {
    if (N <= 0 || K < 0) {
        throw std::invalid_argument("N must be > 0, K must be >= 0.");
    }
}

void BoardSimulation::mark_cell_and_neighbours(std::vector<std::vector<bool>>& board, int r, int c) {
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            int nr = r + dr;
            int nc = c + dc;

            if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                board[nr][nc] = true;
            }
        }
    }
}

long long BoardSimulation::single_simulation(BoardCellPicker& picker) {
    std::vector<std::vector<bool>> board(N, std::vector<bool>(N, false));

    for (int i = 0; i < K; ++i) {
        Cell selected_cell = picker();
        mark_cell_and_neighbours(board, selected_cell.row, selected_cell.col);
    }

    long long free_zone_size = 0;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (!board[r][c]) {
                free_zone_size++;
            }
        }
    }
    return free_zone_size;
}

Result BoardSimulation::multiple_simulations(int num_simulations) {
    if (num_simulations <= 0) {
        throw std::invalid_argument("N must be > 0, K must be >= 0.");
    }

    BoardCellPicker picker(N);
    std::vector<long long> results;
    results.reserve(num_simulations);

    for (int i = 0; i < num_simulations; ++i) {
        results.push_back(single_simulation(picker));
    }

    double total_sum = static_cast<double>(std::accumulate(results.begin(), results.end(), 0LL));
    double mean = total_sum / num_simulations;

    std::sort(results.begin(), results.end());
    double median;
    if (num_simulations % 2 == 1) {
        median = static_cast<double>(results[num_simulations / 2]);
    }
    else {
        long long mid1 = results[num_simulations / 2 - 1];
        long long mid2 = results[num_simulations / 2];
        median = (static_cast<double>(mid1) + mid2) / 2.0;
    }

    return { mean, median };
}