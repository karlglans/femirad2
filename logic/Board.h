#ifndef BOARD
#define BOARD

#include "BoardRow.h"
#include "GoodCellList.h"

#define EMPTY_CELL 0

class Board
{
  static int row;
  //static GoodCellList goodCellList;
  //static void storeGoodCell(short cellIdx, short value);
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
  int evaluatePositions(int team, int* pPosValue);
  bool isValidMove(int move);

  void storeGoodCell(short cellIdx, int value);
  
	Board();
  Board(int row);
	~Board();
};
#endif
