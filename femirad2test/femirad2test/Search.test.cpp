#include "gtest/gtest.h"
#include "../../logic/Search.h"


//TEST(Searching, test1) {
//  Board board(8);
//  char brd[] = {
//    0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0,
//    0, 0, 0, 0, 0, 0, 0, 0 };
//  SearchResult sr;
//  board.setBoard(brd);
//  Search search(3);
//  search.doSearch(sr, 2, &board);
//  EXPECT_EQ(true, true);
//}

//TEST(Searching, test2) {
//  Board board(16);
//  char brd[] = {
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, };
//  
//  brd[120] = 1;
//  brd[119] = 2;
//  brd[136] = 1;
//  brd[135] = 2;
//  SearchResult sr;
//  board.setBoard(brd);
//  Search search(3);
//  search.doSearch(sr, 1, &board);
//  EXPECT_EQ(sr.move, 103);
//}

//TEST(Searching, test2) {
//  Board board(16);
//  char brd[] = {
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, };
//
//  //brd[120] = 1;
//  //brd[119] = 2;
//  //brd[136] = 1;
//  //brd[135] = 2;
//  SearchResult sr;
//  board.setBoard(brd);
//  Search search(3);
//  search.doSearch(sr, 1, &board);
//  EXPECT_EQ(sr.move, 136);
//}


//TEST(Searching, slowTest) {
//  Board board(16);
//  char brd[] = {
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, };
//  board.setBoard(brd);
//
//  board.setCell(120, 1);
//  board.setCell(135, 2);
//  board.setCell(119, 1);
//  board.setCell(136, 2);
//  board.setCell(103, 1);
//  board.setCell(137, 2);
//  board.setCell(138, 1);
//  board.setCell(151, 2);
//  board.setCell(121, 1);
//  board.setCell(118, 2);
//
//  // takes 
//  // 91693 ms
//  // 91787 ms
//
//  SearchResult sr;
//  Search search(3);
//  search.doSearch(sr, 1, &board);
//  EXPECT_EQ(sr.move, 106);
//}