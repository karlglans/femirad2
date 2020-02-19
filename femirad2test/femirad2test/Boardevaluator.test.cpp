#include "gtest/gtest.h"
#include "../../logic/Board.h"
#include "../../logic/ranking.h"
#include "../../logic/Boardevaluator.h"

TEST(Boardevaluator_evaluate, corners_should_have_same_value) {
  const int row = 8;
  Board board(row);
  char brd[] = {
    0, 0, 0, 0, 0, 0, 0, 0, // 0 7
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0 }; // 56 63
  board.setBoard(brd);
  const int boardSize = row * row;
  int* boardValues = new int[boardSize];
  Boardevaluator boardEval;
  int eval = boardEval.evaluateBoard(brd, boardValues, row, 1);
  // 3 fives in 3 diff directions should be possible in each corner
  const int first_corner = boardValues[0];
  EXPECT_EQ(boardValues[7], first_corner);
  EXPECT_EQ(boardValues[56], first_corner);
  EXPECT_EQ(boardValues[63], first_corner);
  delete[] boardValues;
}

TEST(Boardevaluator_evaluate, symmetry_next_to_corners) {
  const int row = 8;
  Board board(row);
  char brd[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, // 9 14
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, // 47 54
    0, 0, 0, 0, 0, 0, 0, 0 }; // 56 63
  board.setBoard(brd);
  const int boardSize = row * row;
  int* boardValues = new int[boardSize];
  Boardevaluator boardEval;
  int eval = boardEval.evaluateBoard(brd, boardValues, row, 1);
  // 3 diff directions should have 2 compleate sequenses 
  const int value_one_step_from_first_corner = boardValues[9];
  EXPECT_EQ(boardValues[14], value_one_step_from_first_corner);
  EXPECT_EQ(boardValues[49], value_one_step_from_first_corner);
  EXPECT_EQ(boardValues[54], value_one_step_from_first_corner);
  delete[] boardValues;
}

TEST(Boardevaluator, calcCellLineValue_emptySpaceLine) {
  Boardevaluator boardEval;
  int line[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, };
  int value = boardEval.calcCellLineValue(line);
  EXPECT_EQ(value, 5*5*2);
}

TEST(Boardevaluator, calcCellLineValue_5_empty_last_spots) {
  Boardevaluator boardEval;
  int line[] = { 3, 3, 3, 3, 0, 0, 0, 0, 0 };
  int value = boardEval.calcCellLineValue(line);
  EXPECT_EQ(value, 5*2);
}

TEST(Boardevaluator, calcCellLineValue_5_empty__first_spots) {
  Boardevaluator boardEval;
  int line[] = { 0, 0, 0, 0, 0, 3, 3, 3, 3 };
  int value = boardEval.calcCellLineValue(line);
  EXPECT_EQ(value, 5 * 2);
}

TEST(Boardevaluator, calcCellLineValue_can_find_win) {
  Boardevaluator boardEval;
  int line[] = { 1, 1, 1, 1, 0, 2, 0, 0, 0 };
  int value = boardEval.calcCellLineValue(line);
  EXPECT_GE(value, fiveInRow); // fiveInRow
}

//TEST(Boardevaluator, calcCellLineValue_10000) {
//  Boardevaluator boardEval;
//  int line[] = { 1, 0, 0, 0, 0, 2, 2, 2, 2 };
//  int value = boardEval.calcCellLineValue(line);
//  EXPECT_EQ(value, 6);
//}

//TEST(Boardevaluator, calcCellLineValue_10000_00000) {
//  Boardevaluator boardEval;
//  int line[] = { 1, 0, 0, 0, 0, 0, 2, 2, 2 };
//  int value = boardEval.calcCellLineValue(line);
//  EXPECT_EQ(value, 6 + 5);
//}

TEST(Boardevaluator, best_cell_should_be_136) {
  const int row = 16;
  Board board(row);
  char brd[] = {
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,0, // cell 119

    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, // cell 136
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, };
  EXPECT_EQ(brd[119], 1);
  int cellValues[16 * 16];
  short cellIdx[16 * 16];
  board.setBoard(brd);
  const int boardSize = row * row;
  Boardevaluator boardEval;
  int eval = boardEval.evaluateBoard(brd, cellValues, row, 2);
  boardEval.sortCellValues(cellValues, cellIdx, boardSize, 10);
  const int bestCellId = 135;
  int value = boardEval.evaluateCell(bestCellId, brd, row, 2);
  EXPECT_EQ(cellIdx[0], bestCellId);
  EXPECT_EQ(cellValues[bestCellId], value);
}