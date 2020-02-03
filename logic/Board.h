#ifndef BOARD
#define BOARD

#include "BoardRow.h"

class Board
{
  static int row;
private:
	char _board[BOARD_ROW * BOARD_ROW];
public:
	const char* getBoard();
  void clean();
	void setBoard(const char* board);
  void setRow(int row);
  void copyBoard(Board* from);
  void copyBoard(char* to);
  int getRow();
  int getSize();
  void setCell(int cellIdx, int player);
  int evaluateWin(int team);
  int evaluate(int team);
  bool isValidMove(int move);
	Board();
  Board(int row);
	~Board();
};
#endif