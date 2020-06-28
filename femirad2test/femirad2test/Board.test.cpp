#include "gtest/gtest.h"
#include "../../logic/Game.h"
#include "../../logic/Board.h"
#include "../../logic/ranking.h"

TEST(Board, setBoard) {
  Board board(8);
  char brd[] = { 
    1, 2, 3, 4, 5, 6, 7, 8,
    2, 2, 3, 4, 5, 6, 7, 8, 
    3, 2, 3, 4, 5, 6, 7, 8, 
    4, 2, 3, 4, 5, 6, 7, 8, 
    5, 2, 3, 4, 5, 6, 7, 8, 
    6, 2, 3, 4, 5, 6, 7, 8, 
    7, 2, 3, 4, 5, 6, 7, 8, 
    8, 2, 3, 4, 5, 6, 7, 8 };
  board.setBoard(brd);
  const char* boardPtr = board.getBoard();
  EXPECT_EQ(boardPtr[1], 2);
}

TEST(Board_copyBoard, setBoard) {
  Board board(8);
  char brd[] = {
    1, 2, 0, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1 };
  board.setBoard(brd);
  Board board2(8);
  board2.copyBoard(&board);
  const char* boardData = board2.getBoard();
  EXPECT_EQ(boardData[1], 2);
  EXPECT_EQ(boardData[2], 0);
}

TEST(Board_isValidMove, will_not_accept_out_of_range_move) {
  Board board(8);
  EXPECT_EQ(board.isValidMove(100), false);
}

TEST(Board_isValidMove, will_accept_move_when_cell_is_free) {
  Board board(8);
  char brd[] = {
    0, 0, 0, 1, 1, 1, 1, 1, // 2: free
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 0, 0, 0, };
  board.setBoard(brd);
  EXPECT_EQ(board.isValidMove(2), true);
}

TEST(Board_isValidMove, will_not_accept_move_when_cell_is_taken) {
  Board board(8);
  char brd[] = {
    0, 0, 0, 1, 1, 1, 1, 1, // 4: taken by 1
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 0, 0, 0, };
  board.setBoard(brd);
  EXPECT_EQ(board.isValidMove(4), false);
}

TEST(Board, evaluateWin_can_detect_horizontal_line) {
  Board board(8);
  char brd[] = {
    0, 0, 0, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 0, 0, 0, };
  board.setBoard(brd);
  EXPECT_EQ(board.evaluateWin(1), 3 * fiveInRow);
}

TEST(Board, getCellPly0) {
  Board board(16);
  EXPECT_EQ(board.getCellPly0(), 119);
}

