#include "Board.h"
#include "ranking.h"

int Board::row = 16;

Board::Board()
{
}

void Board::clean() {
  for (int c = 0; c < getSize(); c++) {
    _board[c] = EMPTY_CELL;
  }
}

Board::Board(int row) { Board::row = row; }

Board::~Board()
{
}

void Board::setBoard(const char* board)
{
	const int size = row * row;
	for (int i = 0; i < size; i++) {
    switch (board[i]) {
      case 0: _board[i] = 0; break;
      case 1: _board[i] = 1; break;
      case 2: _board[i] = 2; break;
      default: _board[i] = 0; break; // any value but 1 2 will be 0
    }
	}
}

int Board::getCellPly0() {
  const int upperHalf = row * ((row - 1) / 2);
  return upperHalf + (row / 2) - 1;
}

const char* Board::getBoard()
{
  return _board;
}

void Board::setRow(const int row)
{
  Board::row = row;
}

void Board::copyBoard(Board* srcBoard)
{
  const int size = srcBoard->getSize();
  const char* srcBoardData = srcBoard->getBoard();
  for (int i = 0; i < size; i++) {
    _board[i] = srcBoardData[i];
  }
}

void Board::copyBoard(char* dest)
{
  const int size = getSize();
  for (int i = 0; i < size; i++) {
    dest[i] = _board[i];
  }
}

int Board::getRow()
{
  return Board::row;
}

int Board::getSize()
{
  return row * row;
}

void Board::setCell(int cellIdx, int player)
{
  _board[cellIdx] = player;
}

bool Board::isValidMove(const int move) {
  if (move >= row * row) return false;
  // TODO m
  return _board[move] == 0;
}

// TODO idea: just look examine the area around the last changed cell
int Board::evaluateWin(const int team) {
  const int row = Board::row;
  const char* _board = this->_board;
  int accValue = 0; // consider maybe not accumelate points, instead just return after 5 cells in row

  // combines vertical and horizontal 
  int i, j, idxHor = 0, idxVer = 0, horLineCount = 0, verLineCount = 0;
  for (j = 0; j < row; j++) {
    horLineCount = 0;
    idxVer = j;
    for (i = 0; i < row; i++) {
      if (_board[idxHor] == team) {
        horLineCount += 1;
        if (horLineCount == 5) {
          accValue += fiveInRow;
          horLineCount = 0;
        }
      } else {
        horLineCount = 0;
      }
      if (_board[idxVer] == team) {
        verLineCount += 1;
        if (verLineCount == 5) {
          accValue += fiveInRow;
          verLineCount = 0;
        }
      } else {
        verLineCount = 0;
      }
      // orthogonal steps
      idxVer += row;
      idxHor += 1;
    }
  }

  // combines falling/rising lines
  const int firstIndexLastRow = row * (row - 1);
  const int lastIndex = row * row - 1;
  const int maxJ = row * 2 - 5;
  int offestI = 0;
  int idxFall, idxRise, fallLineCellCount = 0, riseLineCellCount = 0;
  const int risingStep = -row - 1, fallingStep = -row + 1;
  for (j = 4; j < maxJ; j++) {
    if (j < row) {
      idxFall = j * row; // first in row
      idxRise = (j + 1) * row - 1; // last in row
      i = 0;
    } else { // after stepping out of bottom of NxN we are gonna follow last row
      offestI += 1;
      i = offestI;
      idxFall = firstIndexLastRow + offestI;
      idxRise = lastIndex - offestI;
    }
    for (; i < row; i++) {
      if (idxFall < 0) {
        i = row;
        continue;
      }
      if (_board[idxFall] == team) {
        fallLineCellCount++;
        if (fallLineCellCount == 5) {
          accValue += fiveInRow;
          fallLineCellCount = 0;
        }
      }
      else {
        fallLineCellCount = 0;
      }
      if (_board[idxRise] == team) {
        riseLineCellCount++;
        if (riseLineCellCount == 5) {
          accValue += fiveInRow;
          riseLineCellCount = 0;
        }
      } else {
        riseLineCellCount = 0;
      }
      // vertical steps upwards towards index 0
      idxFall += fallingStep;
      idxRise += risingStep;
    }
  }
  return accValue; // accValue
}

