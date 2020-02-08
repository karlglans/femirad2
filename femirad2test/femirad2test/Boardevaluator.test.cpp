#include "gtest/gtest.h"
#include "../../logic/Board.h"
#include "../../logic/ranking.h"
#include "../../logic/Boardevaluator.h"


//TEST(Boardevaluator, cells2_open) {
//  const int row = 8;
//  Board board(row);
//  char brd[] = {
//    0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, // 12 13 14 15
//    0, 0, 0, 0, 0, 1, 1, 0, // 20  x  x 23
//    0, 0, 0, 0, 0, 0, 0, 0, // 28 29 30 31
//    0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0 };
//  board.setBoard(brd);
//  const int boardSize = row * row;
//  int* boardValues = new int[boardSize];
//  Boardevaluator boardEval;
//  int eval = boardEval.evaluate(brd, boardValues, row, 1);
//  EXPECT_EQ(boardValues[12], open2cells);
//  EXPECT_EQ(boardValues[13], open2cells); 
//  EXPECT_EQ(boardValues[14], 2 * open2cells);
//  EXPECT_EQ(boardValues[15], semiOpen2cells);
//  EXPECT_EQ(boardValues[20], open3cells);
//  EXPECT_EQ(boardValues[23], semiOpen3cells);
//  EXPECT_EQ(boardValues[28], open2cells);
//  EXPECT_EQ(boardValues[29], 2 * open2cells);
//  EXPECT_EQ(boardValues[30], 2 * open2cells);
//  EXPECT_EQ(boardValues[31], 0);
//  delete[] boardValues;
//}
//
//TEST(Boardevaluator, semiopen_closed_by_leftrigh) {
//  const int row = 8;
//  Board board(row);
//  char brd[] = {
//    0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, //            13 14 15
//    0, 0, 0, 0, 0, 0, 1, 1, //            21  x  x
//    0, 0, 0, 0, 0, 0, 0, 0, // 24 25 26   29 30 31
//    1, 1, 0, 0, 0, 0, 0, 0, // x  x  34
//    0, 0, 0, 0, 0, 0, 0, 0, // 40 41 42
//    0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0 };
//  board.setBoard(brd);
//  const int boardSize = row * row;
//  int* boardValues = new int[boardSize];
//  Boardevaluator boardEval;
//  int eval = boardEval.evaluate(brd, boardValues, row, 1);
//  // right side
//  EXPECT_EQ(boardValues[13], 0);
//  EXPECT_EQ(boardValues[14], open2cells);
//  EXPECT_EQ(boardValues[15], open2cells + semiOpen2cells);
//  EXPECT_EQ(boardValues[21], semiOpen3cells);
//  EXPECT_EQ(boardValues[22], 0);
//  EXPECT_EQ(boardValues[23], 0);
//  EXPECT_EQ(boardValues[29], open2cells);
//  EXPECT_EQ(boardValues[30], open2cells + semiOpen2cells);
//  // right side
//  EXPECT_EQ(boardValues[24], open2cells + semiOpen2cells);
//  EXPECT_EQ(boardValues[25], open2cells + semiOpen2cells);
//  EXPECT_EQ(boardValues[26], open2cells);
//  EXPECT_EQ(boardValues[32], 0);
//  EXPECT_EQ(boardValues[33], 0);
//  EXPECT_EQ(boardValues[34], semiOpen3cells);
//  EXPECT_EQ(boardValues[40], open2cells + semiOpen2cells);
//  EXPECT_EQ(boardValues[41], open2cells);
//  EXPECT_EQ(boardValues[42], open2cells);
//  delete[] boardValues;
//}

TEST(Boardevaluator, semiopen_closed_by_opponent) {
  const int row = 8;
  Board board(row);
  char brd[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 2, 0, 0, 0, // 18 19 x 21
    0, 0, 0, 1, 1, 2, 0, 0, // 34 x  x  x
    0, 0, 0, 0, 0, 0, 0, 0, // 42 43 44 45 
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0 };
  board.setBoard(brd);
  const int boardSize = row * row;
  int* boardValues = new int[boardSize];
  Boardevaluator boardEval;
  int eval = boardEval.evaluate(brd, boardValues, row, 1);
  EXPECT_EQ(boardValues[18], open2cells);
  EXPECT_EQ(boardValues[19], 2 * open2cells);
  EXPECT_EQ(boardValues[20], 0);
  EXPECT_EQ(boardValues[21], open2cells);
  EXPECT_EQ(boardValues[34], semiOpen3cells);

  delete[] boardValues;
}