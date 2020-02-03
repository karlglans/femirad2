#include "Board.h"
#include "ranking.h"

int Board::row = 16;

Board::Board()
{
}

void Board::clean() {
  for (int c = 0; c < getSize(); c++) {
    _board[c] = 0;
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
    _board[i] = board[i];
	}
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
  //debug_countItt += 1;
  return accValue; // accValue
}

const int cellTypeOpen = 0; // could still be taken

int Board::evaluate(int team) {
  //const { board, row } = this;
  const int row = this->row;
  const char* board = this->_board;
  int accValue = 0; // consider maybe not accumelate points, instead just return after 5 cells in row

  // combines vertical and horizontal search for lines
  int i, j, idxHor = 0, idxVer = 0, horLineCount = 0, verLineCount = 0;
  const int rowMax = row - 1;
  int isLastRowI;
  bool horOpenBegining, verOpenBegining = false;
  int countClosedSides;
  for (j = 0; j < row; j++, verLineCount = 0, verOpenBegining = false) {
    horLineCount = 0;
    idxVer = j;
    horOpenBegining = false;
    for (i = 0; i < row; i++) {

      // ****************** horizontal block ******************

      isLastRowI = i == rowMax;

      // count horizontal points
      if (horLineCount > 0 && (isLastRowI || board[idxHor] != team)) {
        if (isLastRowI && board[idxHor] == team) horLineCount += 1;
        if (horLineCount > 1) {
          countClosedSides = board[idxHor] != cellTypeOpen ? 1 : 0;
          if (!horOpenBegining) countClosedSides += 1;
          if (countClosedSides < 2) {
            if (horLineCount == 2) accValue += countClosedSides == 0 ? open2cells : semiOpen2cells;
            else if (horLineCount == 3) accValue += countClosedSides == 0 ? open3cells : semiOpen3cells;
            else if (horLineCount == 4) {
              if (countClosedSides == 0) return open4row; // vitory!
              else accValue += semiOpen4row;
            }
          }
        }
      }
      // prep for next itteration
      if (!isLastRowI && board[idxHor] == team) {
        horLineCount += 1;
      } else {
        horOpenBegining = board[idxHor] == cellTypeOpen;
        horLineCount = 0;
      }

      // ****************** vertical block *******************

      // count vertical points
      if (verLineCount > 0 && (isLastRowI || board[idxVer] != team)) {
        if (isLastRowI && board[idxVer] == team) verLineCount += 1;
        if (verLineCount > 1) {
          countClosedSides = board[idxVer] != cellTypeOpen ? 1 : 0;
          if (!verOpenBegining) countClosedSides += 1;
          if (countClosedSides < 2) {
            if (verLineCount == 2) accValue += countClosedSides == 0 ? open2cells : semiOpen2cells;
            else if (verLineCount == 3) accValue += countClosedSides == 0 ? open3cells : semiOpen3cells;
            else if (verLineCount == 4) {
              if (countClosedSides == 0) return open4row; // vitory!
              else accValue += semiOpen4row;
            }
          }
        }
      }
      // prep for next itteration
      if (!isLastRowI && board[idxVer] == team) {
        verLineCount += 1;
      } else {
        verOpenBegining = board[idxVer] == cellTypeOpen;
        verLineCount = 0;
      }

      // orthogonal steps
      idxVer += row;
      idxHor += 1;
    }
  }

  // combines search in two directions by diagonal lines.
  // Stepping upwords from sides till hitting indices lower then 0.
  // Also 'extending' nxn board when reaching bottom by changing direction (from i to j),
  // to be able to reach evry diagonal.

  //         i -->
  //       0  2  3  *  *  5
  //   j   6  *  r  f  *  *
  //   |   *  r  *  *  f  *
  //   v   r  *  *  *  *  f   rising, falling diagonals  

  const int firstIndexLastRow = row * (row - 1);
  const int lastIndex = row * row - 1;
  const int maxJ = row * 2 - 3;
  int offestI = 0;
  int idxFall, idxRise, fallLineCellCount = 0, riseLineCellCount = 0;
  const int risingStep = -row - 1, fallingStep = -row + 1;
  bool fallOpenBegining = false, riseOpenBegining = false;
  const int startOffsetDown = 2; // enogh to fit in 3 cells in diagonal, for detecting semi-open 2 line
  for (j = startOffsetDown; j < maxJ; j++) {
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
    fallOpenBegining = false;
    riseOpenBegining = false;
    for (; i < row; i++) {

      if (idxFall < 0) {
        i = row;
        continue;
      }
      // reched end of line, that is special horizontal line
      isLastRowI = i == rowMax || idxFall < row;

      if (fallLineCellCount > 0 && (isLastRowI || board[idxFall] != team)) {
        if (isLastRowI && board[idxFall] == team) fallLineCellCount += 1;
        if (fallLineCellCount > 1) {
          countClosedSides = board[idxFall] != cellTypeOpen ? 1 : 0;
          if (!fallOpenBegining) countClosedSides += 1;
          if (countClosedSides < 2) {
            if (fallLineCellCount == 2) accValue += countClosedSides == 0 ? open2cells : semiOpen2cells;
            else if (fallLineCellCount == 3) accValue += countClosedSides == 0 ? open3cells : semiOpen3cells;
            else if (fallLineCellCount == 4) {
              if (countClosedSides == 0) return open4row; // vitory!
              else accValue += semiOpen4row;
            }
          }
        }
      }

      // prep for next itteration
      if (!isLastRowI && board[idxFall] == team) {
        fallLineCellCount += 1;
      } else {
        fallOpenBegining = board[idxFall] == cellTypeOpen;
        fallLineCellCount = 0;
      }

      if (riseLineCellCount > 0 && (isLastRowI || board[idxRise] != team)) {
        if (isLastRowI && board[idxRise] == team) riseLineCellCount += 1;
        if (riseLineCellCount > 1) {
          countClosedSides = board[idxRise] != cellTypeOpen ? 1 : 0;
          if (!riseOpenBegining) countClosedSides += 1;
          if (countClosedSides < 2) {
            if (riseLineCellCount == 2) accValue += countClosedSides == 0 ? open2cells : semiOpen2cells;
            else if (riseLineCellCount == 3) accValue += countClosedSides == 0 ? open3cells : semiOpen3cells;
            else if (riseLineCellCount == 4) {
              if (countClosedSides == 0) return open4row; // vitory!
              else accValue += semiOpen4row;
            }
          }
        }
      }

      // prep for next itteration
      if (!isLastRowI && board[idxRise] == team) {
        riseLineCellCount += 1;
      } else {
        riseOpenBegining = board[idxRise] == cellTypeOpen;
        riseLineCellCount = 0;
      }

      // vertical steps upwards towards index 0
      idxFall += fallingStep;
      idxRise += risingStep;
    }
    fallLineCellCount = 0;
    riseLineCellCount = 0; // tveksam
  }

  return accValue;
}
