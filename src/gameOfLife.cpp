#include "gameOfLife.hpp"

#include <cstdint>
#include <functional>
#include <iostream>
#include <ranges>

namespace {

using Rule = std::function<bool(bool state, size_t liveNeighbours)>;
constexpr std::array rules = {underpopulation, nextGeneration, overpopulation,
                              reproduction};

constexpr bool applyRules(bool state, size_t liveNeighbours) {
  for (const auto& rule : rules) state = rule(state, liveNeighbours);
  return state;
}

bool isAlive(const Grid& grid, std::int64_t row, std::int64_t col) {
  if (row < 0 || row >= grid.size()) return false;
  if (col < 0 || col >= grid[row].size()) return false;
  return grid[row][col];
}

size_t liveNeighbours(const Grid& grid, std::int64_t row, std::int64_t col) {
  size_t liveNeighbours{};
  liveNeighbours += isAlive(grid, row + 1, col - 1);  // top left
  liveNeighbours += isAlive(grid, row + 1, col);      // top
  liveNeighbours += isAlive(grid, row + 1, col + 1);  // top right
  liveNeighbours += isAlive(grid, row, col - 1);      // left
  liveNeighbours += isAlive(grid, row, col + 1);      // right
  liveNeighbours += isAlive(grid, row - 1, col - 1);  // bottom left
  liveNeighbours += isAlive(grid, row - 1, col);      // bottom
  liveNeighbours += isAlive(grid, row - 1, col + 1);  // bottom right
  return liveNeighbours;
}

void clearScreen() { std::cout << "\033[2J\033[1;1H"; }

void printGrid(const Grid& grid) {
  clearScreen();
  for (const auto& row : grid) {
    for (const auto cell : row) {
      std::cout << (cell ? "\u2588" : " ");
    }
    std::cout << '\n';
  }
  std::cout << std::flush;
}

}  // namespace

bool underpopulation(bool state, size_t liveNeighbours) {
  if (liveNeighbours < 2) return false;
  return state;
}

bool nextGeneration(bool state, size_t liveNeighbours) {
  if (state && (liveNeighbours == 2 || liveNeighbours == 3)) return true;
  return state;
}

bool overpopulation(bool state, size_t liveNeighbours) {
  if (liveNeighbours > 3) return false;
  return state;
}

bool reproduction(bool state, size_t liveNeighbours) {
  if (liveNeighbours == 3) return true;
  return state;
}

Grid gameOfLife(const Grid& input, size_t iterations) {
  // Global grid to be updated each iteration
  Grid grid{input};
  for (auto i{0}; i < iterations; ++i) {
    // Grid to hold intermediatry results of each iteration
    Grid newGrid{grid};

    // Loop over cells and apply rules to get new grid
    for (auto&& [rowIdx, row] : grid | std::views::enumerate) {
      for (auto&& [colIdx, cell] : row | std::views::enumerate) {
        // Apply rules to current cell
        newGrid[rowIdx][colIdx] = applyRules(
            grid[rowIdx][colIdx], liveNeighbours(grid, rowIdx, colIdx));
      }
    }
    grid = std::move(newGrid);
    printGrid(grid);
  }

  return grid;
}
