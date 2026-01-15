#include <gtest/gtest.h>

#include "gameOfLife.hpp"
#include "gtest/gtest.h"

namespace testing {
namespace {

struct RuleParams {
  bool state;
  size_t liveNeighbours;
  bool expected;
};

struct GameOfLifeParams {
  Grid input;
  size_t iterations;
  Grid expected;
};

class GameOfLife : public ::testing::TestWithParam<GameOfLifeParams> {};
class RuleUnderpopulation : public ::testing::TestWithParam<RuleParams> {};
class RuleNextGeneration : public ::testing::TestWithParam<RuleParams> {};
class RuleOverpopulation : public ::testing::TestWithParam<RuleParams> {};
class RuleReproduction : public ::testing::TestWithParam<RuleParams> {};

}  // namespace

TEST_P(GameOfLife, Full) {
  const auto& data = GetParam();
  EXPECT_EQ(data.expected, gameOfLife(data.input, data.iterations));
}

TEST_P(RuleUnderpopulation, Underpopulation) {
  const auto& data = GetParam();
  EXPECT_EQ(data.expected, underpopulation(data.state, data.liveNeighbours));
}
TEST_P(RuleNextGeneration, NextGeneration) {
  const auto& data = GetParam();
  EXPECT_EQ(data.expected, nextGeneration(data.state, data.liveNeighbours));
}
TEST_P(RuleOverpopulation, Overpopulation) {
  const auto& data = GetParam();
  EXPECT_EQ(data.expected, overpopulation(data.state, data.liveNeighbours));
}
TEST_P(RuleReproduction, Reproduction) {
  const auto& data = GetParam();
  EXPECT_EQ(data.expected, reproduction(data.state, data.liveNeighbours));
}

INSTANTIATE_TEST_SUITE_P(
    , GameOfLife,
    ::testing::Values(
        GameOfLifeParams{.input = Grid{{1, 1, 0}, {0, 1, 0}, {0, 1, 1}},
                         .iterations = 1,
                         .expected = Grid{{1, 1, 0}, {0, 0, 0}, {0, 1, 1}}},
        GameOfLifeParams{.input = Grid{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                         .iterations = 1,
                         .expected = Grid{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}));

INSTANTIATE_TEST_SUITE_P(
    , RuleUnderpopulation,
    ::testing::Values(
        // dies
        RuleParams{.state = true, .liveNeighbours = 0, .expected = false},
        RuleParams{.state = true, .liveNeighbours = 1, .expected = false},
        // dont change
        RuleParams{.state = true, .liveNeighbours = 2, .expected = true},
        RuleParams{.state = false, .liveNeighbours = 2, .expected = false}));

INSTANTIATE_TEST_SUITE_P(
    , RuleNextGeneration,
    ::testing::Values(
        // lives
        RuleParams{.state = true, .liveNeighbours = 2, .expected = true},
        RuleParams{.state = true, .liveNeighbours = 3, .expected = true},
        // dont change
        RuleParams{.state = true, .liveNeighbours = 1, .expected = true},
        RuleParams{.state = false, .liveNeighbours = 1, .expected = false},
        RuleParams{.state = true, .liveNeighbours = 4, .expected = true},
        RuleParams{.state = false, .liveNeighbours = 4, .expected = false}));

INSTANTIATE_TEST_SUITE_P(
    , RuleOverpopulation,
    ::testing::Values(
        // dies
        RuleParams{.state = true, .liveNeighbours = 4, .expected = false},
        RuleParams{.state = true, .liveNeighbours = 5, .expected = false},
        // dont change
        RuleParams{.state = true, .liveNeighbours = 3, .expected = true},
        RuleParams{.state = false, .liveNeighbours = 3, .expected = false},
        RuleParams{.state = true, .liveNeighbours = 2, .expected = true},
        RuleParams{.state = false, .liveNeighbours = 2, .expected = false}));

INSTANTIATE_TEST_SUITE_P(
    , RuleReproduction,
    ::testing::Values(
        // lives
        RuleParams{.state = false, .liveNeighbours = 3, .expected = true},
        // dont change
        RuleParams{.state = true, .liveNeighbours = 3, .expected = true},
        RuleParams{.state = true, .liveNeighbours = 2, .expected = true},
        RuleParams{.state = false, .liveNeighbours = 2, .expected = false},
        RuleParams{.state = true, .liveNeighbours = 4, .expected = true},
        RuleParams{.state = false, .liveNeighbours = 4, .expected = false}));

}  // namespace testing
