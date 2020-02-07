#include "gtest/gtest.h"
#include "../../logic/Game.h"
#include "../../logic/Board.h"
#include "../../logic/ranking.h"

const int no_wrong_position = -1;
// helper function. Only free board cells should have a matching value
int firstClaimedPositionWithValue(char* board, int* cellValues, int size) {
  for (int i = 0; i < size; i++) {
    if (board[i] != 0 && cellValues[i] != 0) return i;
  }
  return no_wrong_position;
}

TEST(Board_evaluatePositions, horizontal_open_free) {
  Board board(8);
  // In these situations giving same points at both ends
  char brd[] = {
    0, 0, 0, 1, 1, 0, 0, 0, // 2 & 5
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0, // 18 & 22
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0 }; 
  board.setBoard(brd);
  const int boardSize = 8 * 8;
  int* boardValues = new int[boardSize];
  memset(boardValues, 0, sizeof(int) * boardSize);
  board.evaluatePositions(1, boardValues);
  EXPECT_EQ(boardValues[2], open3cells);
  EXPECT_EQ(boardValues[5], open3cells);
  EXPECT_EQ(boardValues[18], open4cells);
  EXPECT_EQ(boardValues[22], open4cells);
  int wrongBoardValueIndex = firstClaimedPositionWithValue(brd, boardValues, boardSize);
  EXPECT_EQ(wrongBoardValueIndex, no_wrong_position);
  delete[] boardValues;
}

TEST(Board_evaluatePositions, horizontal_open_1side) {
  Board board(8);
  // In these situations giving less points to the side near edge, since the result will be semiclosed
  char brd[] = {
    0, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 0, // 19 23
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 0, 0, 1, 1, 0, // 32 35 36 39
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 0, 0, 0 }; // 56  61
  board.setBoard(brd);
  const int boardSize = 8 * 8;
  int* boardValues = new int[boardSize];
  memset(boardValues, 0, sizeof(int) * boardSize);
  board.evaluatePositions(1, boardValues);
  EXPECT_EQ(boardValues[0], semiOpen4cells);
  EXPECT_EQ(boardValues[4], open4cells);
  EXPECT_EQ(boardValues[19], open4cells);
  EXPECT_EQ(boardValues[23], semiOpen4cells);
  EXPECT_EQ(boardValues[32], semiOpen3cells);
  EXPECT_EQ(boardValues[36], open3cells);
  EXPECT_EQ(boardValues[39], semiOpen3cells);
  EXPECT_EQ(boardValues[56], fiveInRow);
  EXPECT_EQ(boardValues[61], fiveInRow);
  int wrongBoardValueIndex = firstClaimedPositionWithValue(brd, boardValues, boardSize);
  EXPECT_EQ(wrongBoardValueIndex, no_wrong_position);
  delete[] boardValues;
}

TEST(Board_evaluatePositions, horizontal_2semiopen_closedright_by_edge) {
  Board board(10);
  char brd[] = {
    0, 0, 0, 0, 2, 0, 0, 0, 1, 1, // 7
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 1, 1, // 27 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 0, 0, 1, 1, // 47
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 0, 0, 0, 1, 1, 2, // 66
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 2, 0, 0, 1, 1, 2, // 86
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
  board.setBoard(brd);
  const int boardSize = 10 * 10;
  int* boardValues = new int[boardSize];
  memset(boardValues, 0, sizeof(int) * boardSize);
  board.evaluatePositions(1, boardValues);
  EXPECT_EQ(boardValues[7], semiOpen3cells); // room for 5 cells after the prev 2
  EXPECT_EQ(boardValues[27], semiOpen3cells); // room for 5 including the prev 1 
  EXPECT_EQ(boardValues[47], 0); // no room for 5 cells
  EXPECT_EQ(boardValues[66], semiOpen3cells); // room for 5 cells after the prev 2
  EXPECT_EQ(boardValues[86], 0); // no room for 5 cells
  int wrongBoardValueIndex = firstClaimedPositionWithValue(brd, boardValues, boardSize);
  EXPECT_EQ(wrongBoardValueIndex, -1);
  delete[] boardValues;
}

TEST(Board_evaluatePositions, horizontal_2semiopen_closedright_by_opponent) {
  Board board(10);
  char brd[] = {
    0, 0, 2, 0, 0, 0, 1, 1, 2, 0, // 5 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 1, 1, 2, 0, // 25
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 0, 0, 1, 1, 2, 0, // 45
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 2, 0, 0, 0, 0, // 62
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 2, 0, 0, 0, 0, 0, // 81
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
  board.setBoard(brd);
  const int boardSize = 10 * 10;
  int* boardValues = new int[boardSize];
  memset(boardValues, 0, sizeof(int) * boardSize);
  board.evaluatePositions(1, boardValues);
  EXPECT_EQ(boardValues[5], semiOpen3cells); // room for 5 cells after the prev 2
  EXPECT_EQ(boardValues[25], semiOpen3cells); // room for 5 cells including the prev 1
  EXPECT_EQ(boardValues[45], 0); // no room for 5 cells
  EXPECT_EQ(boardValues[62], semiOpen3cells);
  EXPECT_EQ(boardValues[81], 0); // no room for 5 cells
  int wrongBoardValueIndex = firstClaimedPositionWithValue(brd, boardValues, boardSize);
  EXPECT_EQ(wrongBoardValueIndex, -1);
  delete[] boardValues;
}

TEST(Board_evaluatePositions, horizontal_2semiopen_closedleft_edge) {
  Board board(10);
  char brd[] = {
    1, 1, 0, 0, 0, 2, 0, 0, 0, 0, // 2
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 1, 0, 0, 0, 0, 0, // 22
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 2, 0, 0, 0, 0, 0, // 42
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
  board.setBoard(brd);
  const int boardSize = 10 * 10;
  int* boardValues = new int[boardSize];
  memset(boardValues, 0, sizeof(int) * boardSize);
  board.evaluatePositions(1, boardValues);
  EXPECT_EQ(boardValues[2], semiOpen3cells);
  EXPECT_EQ(boardValues[22], semiOpen3cells);
  EXPECT_EQ(boardValues[42], 0);
  EXPECT_EQ(boardValues[62], 0);
  int wrongBoardValueIndex = firstClaimedPositionWithValue(brd, boardValues, boardSize);
  EXPECT_EQ(wrongBoardValueIndex, -1);
  delete[] boardValues;
}

TEST(Board_evaluatePositions, horizontal_2semiopen_closedleft_opp) {
  Board board(10);
  char brd[] = {
    0, 0, 0, 0, 2, 1, 1, 0, 0, 0, // 7
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 2, 1, 1, 0, 0, 1, // 27
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 2, 1, 1, 0, 0, 2, // 47
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 2, 1, 1, 0, 2, 0, // 67
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 1, 1, 0, // 89
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
  board.setBoard(brd);
  const int boardSize = 10 * 10;
  int* boardValues = new int[boardSize];
  memset(boardValues, 0, sizeof(int) * boardSize);
  board.evaluatePositions(1, boardValues);
  EXPECT_EQ(boardValues[7], semiOpen3cells);
  EXPECT_EQ(boardValues[27], semiOpen3cells);
  EXPECT_EQ(boardValues[47], 0);
  EXPECT_EQ(boardValues[67], 0);
  EXPECT_EQ(boardValues[89], 0);
  int wrongBoardValueIndex = firstClaimedPositionWithValue(brd, boardValues, boardSize);
  EXPECT_EQ(wrongBoardValueIndex, -1);
  delete[] boardValues;
}

TEST(Board_evaluatePositions, horizontal_3semiopen_closedright_by_edge) {
  Board board(10);
  char brd[] = {
    0, 0, 0, 0, 2, 0, 0, 1, 1, 1, // 7
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 1, 1, 1, // 27 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 0, 1, 1, 1, // 46
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 0, 0, 1, 1, 1, 2, // 66
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 2, 0, 1, 1, 1, 2, // 85
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
  board.setBoard(brd);
  const int boardSize = 10 * 10;
  int* boardValues = new int[boardSize];
  memset(boardValues, 0, sizeof(int) * boardSize);
  board.evaluatePositions(1, boardValues);
  EXPECT_EQ(boardValues[6], semiOpen4cells); // room for 5 cells after the prev 2
  EXPECT_EQ(boardValues[26], semiOpen4cells); // room for 5 including the prev 1 
  EXPECT_EQ(boardValues[46], 0); // no room for 5 cells
  EXPECT_EQ(boardValues[65], semiOpen4cells); // room for 5 cells after the prev 2
  EXPECT_EQ(boardValues[85], 0); // no room for 5 cells
  int wrongBoardValueIndex = firstClaimedPositionWithValue(brd, boardValues, boardSize);
  EXPECT_EQ(wrongBoardValueIndex, -1);
  delete[] boardValues;
}

TEST(Board_evaluatePositions, horizontal_3semiopen_closedright_by_opponent) {
  Board board(10);
  char brd[] = {
    0, 0, 2, 0, 0, 1, 1, 1, 2, 0, // 4
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 1, 1, 1, 2, 0, // 24
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 0, 1, 1, 1, 2, 0, // 44
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 2, 0, 0, 0, 0, // 61
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 2, 0, 0, 0, 0, 0, // 81
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
  board.setBoard(brd);
  const int boardSize = 10 * 10;
  int* boardValues = new int[boardSize];
  memset(boardValues, 0, sizeof(int) * boardSize);
  board.evaluatePositions(1, boardValues);
  EXPECT_EQ(boardValues[4], semiOpen4cells); // room for 5 cells after the prev 2
  EXPECT_EQ(boardValues[24], semiOpen4cells); // room for 5 cells including the prev 1
  EXPECT_EQ(boardValues[44], 0); // no room for 5 cells
  EXPECT_EQ(boardValues[61], semiOpen4cells);
  EXPECT_EQ(boardValues[80], 0); // no room for 5 cells
  int wrongBoardValueIndex = firstClaimedPositionWithValue(brd, boardValues, boardSize);
  EXPECT_EQ(wrongBoardValueIndex, -1);
  delete[] boardValues;
}

TEST(Board_evaluatePositions, horizontal_3semiopen_closedleft_edge) {
  Board board(10);
  char brd[] = {
    1, 1, 1, 0, 0, 2, 0, 0, 0, 0, // 3
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 0, 1, 0, 0, 0, 0, 0, // 23
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 0, 2, 0, 0, 0, 0, 0, // 43
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 2, 0, 0, 0, 0, 0, 0, // 63
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
  board.setBoard(brd);
  const int boardSize = 10 * 10;
  int* boardValues = new int[boardSize];
  memset(boardValues, 0, sizeof(int) * boardSize);
  board.evaluatePositions(1, boardValues);
  EXPECT_EQ(boardValues[3], semiOpen4cells);
  EXPECT_EQ(boardValues[23], semiOpen4cells);
  EXPECT_EQ(boardValues[43], 0);
  EXPECT_EQ(boardValues[62], 0);
  int wrongBoardValueIndex = firstClaimedPositionWithValue(brd, boardValues, boardSize);
  EXPECT_EQ(wrongBoardValueIndex, -1);
  delete[] boardValues;
}

TEST(Board_evaluatePositions, horizontal_3semiopen_closedleft_opp) {
  Board board(10);
  char brd[] = {
    0, 0, 0, 0, 2, 1, 1, 0, 0, 0, // 7
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 2, 1, 1, 0, 0, 1, // 27
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 2, 1, 1, 8, 0, 2, // 47
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 2, 1, 1, 8, 2, 0, // 67
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
  board.setBoard(brd);
  const int boardSize = 10 * 10;
  int* boardValues = new int[boardSize];
  memset(boardValues, 0, sizeof(int) * boardSize);
  board.evaluatePositions(1, boardValues);
  EXPECT_EQ(boardValues[7], semiOpen3cells);
  EXPECT_EQ(boardValues[27], semiOpen3cells);
  EXPECT_EQ(boardValues[47], 0);
  EXPECT_EQ(boardValues[67], 0);
  int wrongBoardValueIndex = firstClaimedPositionWithValue(brd, boardValues, boardSize);
  EXPECT_EQ(wrongBoardValueIndex, -1);
  delete[] boardValues;
}

TEST(Board_evaluatePositions, horizontal_semiopen_win) {
  Board board(8);
  char brd[] = {
    0, 0, 2, 1, 1, 1, 1, 0, // 7
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 2, 0, 0, // 16
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, };
  board.setBoard(brd);
  const int boardSize = 8 * 8;
  int* boardValues = new int[boardSize];
  memset(boardValues, 0, sizeof(int) * boardSize);
  board.evaluatePositions(1, boardValues);
  EXPECT_EQ(boardValues[7], fiveInRow); // right win
  EXPECT_EQ(boardValues[16], fiveInRow); // left win
  int wrongBoardValueIndex = firstClaimedPositionWithValue(brd, boardValues, boardSize);
  EXPECT_EQ(wrongBoardValueIndex, no_wrong_position);
  delete[] boardValues;
}


TEST(Board_evaluatePositions, vertical_open_free) {
  Board board(8);
  char brd[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, // 8 & 14
    1, 0, 0, 0, 0, 0, 1, 0, // 18
    1, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0, // 32 
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0 };
  board.setBoard(brd);
  const int boardSize = 8 * 8;
  int* boardValues = new int[boardSize];
  memset(boardValues, 0, sizeof(int) * boardSize);
  board.evaluatePositions(1, boardValues);
  EXPECT_EQ(boardValues[8], open3cells);
  EXPECT_EQ(boardValues[32], open3cells);
  EXPECT_EQ(boardValues[18], open4cells);
  EXPECT_EQ(boardValues[50], open4cells);
  EXPECT_EQ(boardValues[14], fiveInRow);
  EXPECT_EQ(boardValues[54], fiveInRow);
  int wrongBoardValueIndex = firstClaimedPositionWithValue(brd, boardValues, boardSize);
  EXPECT_EQ(wrongBoardValueIndex, no_wrong_position);
  delete[] boardValues;
}

TEST(Board_evaluatePositions, vertical_open_1side) {
  Board board(8);
  char brd[] = {
    0, 0, 0, 0, 0, 0, 0, 0, // 0 & 5 & 7
    1, 0, 0, 0, 0, 1, 0, 1, 
    1, 0, 0, 0, 0, 1, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, // 24 & 31
    0, 0, 0, 1, 0, 0, 0, 0, // 33 & 37
    0, 1, 0, 1, 0, 0, 0, 0, 
    0, 1, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0 }; // 57 & 59
  board.setBoard(brd);
  const int boardSize = 8 * 8;
  int* boardValues = new int[boardSize];
  memset(boardValues, 0, sizeof(int) * boardSize);
  board.evaluatePositions(1, boardValues);
  EXPECT_EQ(boardValues[0], semiOpen3cells);
  EXPECT_EQ(boardValues[24], open3cells);
  EXPECT_EQ(boardValues[7], semiOpen3cells);
  EXPECT_EQ(boardValues[31], open3cells);
  EXPECT_EQ(boardValues[33], open3cells);
  EXPECT_EQ(boardValues[57], semiOpen3cells);
  EXPECT_EQ(boardValues[27], open4cells);
  EXPECT_EQ(boardValues[59], semiOpen4cells);
  EXPECT_EQ(boardValues[5], semiOpen4cells);
  EXPECT_EQ(boardValues[37], open4cells);
  int wrongBoardValueIndex = firstClaimedPositionWithValue(brd, boardValues, boardSize);
  EXPECT_EQ(wrongBoardValueIndex, no_wrong_position);
  delete[] boardValues;
}
//
//TEST(Board_evaluatePositions, vertical_semiopen_edges) {
//  Board board(8);
//  char brd[] = {
//    1, 0, 1, 0, 1, 0, 0, 0, 
//    1, 0, 1, 0, 1, 0, 0, 0,
//    0, 0, 1, 0, 1, 0, 0, 0, // 16
//    0, 0, 0, 0, 1, 0, 0, 0, // 26 30
//    0, 0, 0, 0, 0, 0, 1, 0, // 34 36
//    0, 0, 1, 0, 0, 0, 1, 0, // 40
//    1, 0, 1, 0, 0, 0, 1, 0,
//    1, 0, 1, 0, 0, 0, 1, 0 };
//  board.setBoard(brd);
//  int* boardValues = new int[8 * 8];
//  memset(boardValues, 0, sizeof(int) * 8 * 8);
//  board.evaluatePositions(1, boardValues);
//  EXPECT_EQ(boardValues[16], semiOpen3cells);
//  EXPECT_EQ(boardValues[26], semiOpen4cells);
//  EXPECT_EQ(boardValues[40], semiOpen3cells);
//  EXPECT_EQ(boardValues[34], semiOpen4cells);
//  EXPECT_EQ(boardValues[36], fiveInRow);
//  EXPECT_EQ(boardValues[30], fiveInRow);
//  delete[] boardValues;
//}

// inre färdig
//TEST(Board_evaluatePositions, vertical_semiopen_opponent) {
//  Board board(8);
//  char brd[] = {
//    0, 0, 0, 0, 0, 0, 0, 0, // 2 5
//    2, 0, 1, 0, 0, 1, 0, 1,
//    1, 0, 1, 0, 0, 1, 0, 1,
//    1, 0, 2, 0, 2, 1, 0, 1,
//    0, 0, 0, 0, 1, 1, 0, 2, // 32
//    0, 0, 0, 0, 1, 2, 0, 0,
//    0, 0, 0, 0, 1, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0 };
//  board.setBoard(brd);
//  int* boardValues = new int[8 * 8];
//  memset(boardValues, 0, sizeof(int) * 8 * 8);
//  board.evaluatePositions(1, boardValues);
//  //EXPECT_EQ(boardValues[32], semiOpen3cells);
//  //EXPECT_EQ(boardValues[2], semiOpen3cells); // should realy be 0
//  //EXPECT_EQ(boardValues[5], fiveInRow);
//  //EXPECT_EQ(boardValues[7], semiOpen4cells); // should realy be 0
//  EXPECT_EQ(boardValues[60], semiOpen4cells);
//  delete[] boardValues;
//}
