#ifndef BOARD
#define BOARD

#include "BoardRow.h"
#include "GoodCellList.h"

#define EMPTY_CELL 0

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
  int getCellPly0();
  bool isValidMove(int move);
  
	Board();
  Board(int row);
	~Board();
};
#endif
