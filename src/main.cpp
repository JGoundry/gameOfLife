#include "gameOfLife.hpp"

#include <iostream>
#include <random>

namespace {

Grid generateGrid(size_t rows, size_t cols) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::bernoulli_distribution d(0.5);

    Grid grid{rows, std::vector<bool>(cols)};
    for (auto& row : grid)
    {
        for (auto cell : row) {
            cell = d(gen);
        }
    }
    return grid;
}

}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::println(std::cerr, "Usage: {} <rows> <cols> <iterations>", argv[0]);
    }

    size_t iterations = 1000;

    size_t rows = 100;
    size_t cols = rows * 3;


    Grid grid = generateGrid(rows, cols);

    gameOfLife(grid, 1000);

    return 0;
}
