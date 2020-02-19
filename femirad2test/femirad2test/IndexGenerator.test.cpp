#include "gtest/gtest.h"
#include "../../logic/IndexGenerator.h"

#include "../../logic/Board.h"

TEST(IndexGeneratorTest, first_index_should_close_to_center) {
  //  0 1 2 3 4 5 6 7
  //  8 * * * * * * *
  // 16 * * * * * * *  
  // 24 * * C * * * *  Center = 27
  // 32 * * * * * * *
  // 40 * * * * * * * 
  // 48 * * * * * * *
  // 56 * * * * * * 63
  const int someRow = 8;
  IndexGenerator indexGen(someRow);
  const short* indecisFromCenter = indexGen.produceListOfIndecisFromCenter();
  const int some_center_pos = 27;
  const int diff_from_center = indecisFromCenter[0] - some_center_pos;
  const int abs_diff_from_center = diff_from_center > 0 ? diff_from_center: -diff_from_center;
  // should be less then 1 row from center
  EXPECT_GE(someRow, abs_diff_from_center);
}

TEST(IndexGenerator, makeInToOutSortedListOfSurroundingCells) {
  const int row = 4;
  Board board(row);
  char brd[] = {
    0, 0, 0, 0, 
    0, 0, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0 };
  board.setBoard(brd);
  short result[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
  IndexGenerator indexGen(row);
  int nResult = indexGen.makeInToOutSortedListOfSurroundingCells(brd, row, result);
  EXPECT_EQ(result[8], 0); // should not be a 9th result
  EXPECT_EQ(result[7], 3); // bord index 3 is the neighbure (to cell 6) most distant from the bord centre
  EXPECT_EQ(nResult, 8);
}

