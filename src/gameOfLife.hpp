#pragma once

#include <vector>

using Grid = std::vector<std::vector<bool>>;

bool underpopulation(bool state, size_t liveNeighbours);
bool nextGeneration(bool state, size_t liveNeighbours);
bool overpopulation(bool state, size_t liveNeighbours);
bool reproduction(bool state, size_t liveNeighbours);

Grid gameOfLife(const Grid& input, size_t iterations);
