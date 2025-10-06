#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include "Simulation.h"     
#include "CellPicker.h" 

void run_test(int N, int K, int M) {
    if (K < 0) return;

    try {
        BoardSimulation experiment(N, K);
        Result result = experiment.multiple_simulations(M);

        double total_cells = N * N;

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "N=" << N << ", K=" << K << ", M=" << M
            << ": Mean=" << result.mean_size
            << " (" << (result.mean_size / total_cells) * 100.0 << "%)"
            << ", Median=" << result.median_size << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Test Error (N=" << N << ", K=" << K << "): " << e.what() << "\n";
    }
}

int main() {
    const int N_BOARD = 30;
    const int K_PICKS = 50;
    const int M_SIMULATIONS = 5000;

    try {
        std::cout << "Program Experiment. Board " << N_BOARD << "x" << N_BOARD << ". " << N_BOARD * N_BOARD << " cells total.\n";

        std::cout << "\n--- Main Calculation ---\n";
        run_test(N_BOARD, K_PICKS, M_SIMULATIONS);

        std::cout << "\n--- K Dependency Research ---\n";
        const int M_INVESTIGATION = 1000;
        std::vector<int> k_values = { 1, N_BOARD, N_BOARD * 3, N_BOARD * N_BOARD };
        for (int K : k_values) {
            run_test(N_BOARD, K, M_INVESTIGATION);
        }

        std::cout << "\n--- Error Test ---\n";
        run_test(0, 10, 10); // Тест для N=0
        run_test(10, 5, 0);  // Тест для M=0

    }
    catch (const std::exception& e) {
        std::cerr << "\nCRITICAL ERROR: " << e.what() << "\n";
        return 1;
    }
    catch (...) {
        std::cerr << "\nUnknown error.\n";
        return 1;
    }

    std::cout << "\nOperation complete.\n";
    return 0;
}