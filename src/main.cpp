#include <exception>
#include <iostream>
#include <random>
#include <string>

#include "gameOfLife.hpp"

namespace {

Grid generateGrid(size_t rows, size_t cols) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::bernoulli_distribution d(0.5);

  Grid grid{rows, Grid::value_type(cols)};
  for (auto& row : grid) {
    for (auto cell : row) {
      cell = d(gen);
    }
  }
  return grid;
}

}  // namespace

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::println(std::cerr, "Usage: {} <rows> <cols> <iterations>", argv[0]);
    return 1;
  }

  size_t rows{}, cols{}, iterations{};
  try {
    rows = std::stoull(argv[1]);
    cols = std::stoull(argv[2]);
    iterations = std::stoull(argv[3]);
  } catch (const std::exception& e) {
    std::println(std::cerr, "Caught '{}' trying to convert args to nums.",
                 e.what());
  }

  gameOfLife(generateGrid(rows, cols), iterations);

  return 0;
}
