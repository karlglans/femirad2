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
      default: _board[i] = 0; break;
    }
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

void Board::storeGoodCell(short cellIdx, int value) {
  // goodCellList.store(cellIdx, value);
}

// TODO idea: just look examine the area around the last changed cell
int Board::evaluateWin(const int team) {
  const int row = Board::row;
  const char* _board = this->_board;
  int accValue = 0; // consider maybe not accumelate points, instead just return after 5 cells in row

  //goodLookers[0] = -1;

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
        /////// tött
        //if (horLineCount == 4) {
        //  storeGoodCell(idxHor, open4row);
        //}
        ///////
        horLineCount = 0;
      }
      if (_board[idxVer] == team) {
        verLineCount += 1;
        if (verLineCount == 5) {
          accValue += fiveInRow;
          verLineCount = 0;
        }
      } else {
        /////// tött
        //if (verLineCount == 4) {
        //  storeGoodCell(idxVer, open4row);
        //}
        ///////
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
        /////// tött
        //if (fallLineCellCount == 4) {
        //  storeGoodCell(idxFall, open4row);
        //}
        ///////
        fallLineCellCount = 0;
      }
      if (_board[idxRise] == team) {
        riseLineCellCount++;
        if (riseLineCellCount == 5) {
          accValue += fiveInRow;
          riseLineCellCount = 0;
        }
      } else {
        /////// tött
        //if (riseLineCellCount == 4) {
        //  storeGoodCell(idxRise, open4row);
        //}
        ///////
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

// const int cellTypeOpen = 0; // could still be taken

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
          countClosedSides = board[idxHor] != EMPTY_CELL ? 1 : 0;
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
        horOpenBegining = board[idxHor] == EMPTY_CELL;
        horLineCount = 0;
      }

      // ****************** vertical block *******************

      // count vertical points
      if (verLineCount > 0 && (isLastRowI || board[idxVer] != team)) {
        if (isLastRowI && board[idxVer] == team) verLineCount += 1;
        if (verLineCount > 1) {
          countClosedSides = board[idxVer] != EMPTY_CELL ? 1 : 0;
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
        verOpenBegining = board[idxVer] == EMPTY_CELL;
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
          countClosedSides = board[idxFall] != EMPTY_CELL ? 1 : 0;
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
        fallOpenBegining = board[idxFall] == EMPTY_CELL;
        fallLineCellCount = 0;
      }

      if (riseLineCellCount > 0 && (isLastRowI || board[idxRise] != team)) {
        if (isLastRowI && board[idxRise] == team) riseLineCellCount += 1;
        if (riseLineCellCount > 1) {
          countClosedSides = board[idxRise] != EMPTY_CELL ? 1 : 0;
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
        riseOpenBegining = board[idxRise] == EMPTY_CELL;
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

/**
 * Giving each free position a value baed on the value of the structures its can be a part of.
 * Ex: if filling an empty cell will make a 3-cell line, then it will get the value of that 3-cell-line.
 * A cell might contribute to more then one valuable structure.
 */
int Board::evaluatePositions(const int team, int* pPosValue) {
  const int row = this->row;
  const int rowX3 = row * 3;
  const int rowX4 = row * 4;
  const int rowX5 = row * 5;
  const char* board = this->_board;
  int accValue = 0; // consider maybe not accumelate points, instead just return after 5 cells in row

  // combines vertical and horizontal search for lines
  int i, j, idxHor = 0, idxVer = 0, horLineCount = 0, verLineCount = 0;
  const int rowMax = row - 1;
  int isLastRowI;
  bool horOpenBegining, verOpenBegining = false;
  int countClosedSides;
  int countFriendlyPre = 0; // open or same team
  bool openBothEnds;
  int oppTeam = team == 1 ? 2 : 1;
  bool cellIsOppo;
  bool cellIsTeam;
  bool cellIsFree;
  int cell4, cell5;
  for (j = 0; j < row; j++, verLineCount = 0, verOpenBegining = false) {
    horLineCount = 0;
    idxVer = j;
    horOpenBegining = false;
    countFriendlyPre = 0;
    for (i = 0; i < row; i++) {

      // ****************** horizontal block ******************

      isLastRowI = i == rowMax;
      cellIsOppo = board[idxHor] == oppTeam;
      cellIsTeam = board[idxHor] == team;
      cellIsFree = board[idxHor] == 0;

      // count horizontal points
      if (horLineCount > 0 && (isLastRowI || board[idxHor] != team)) {
        if (isLastRowI && board[idxHor] == team) horLineCount += 1;
        if (horLineCount > 1) {
          countClosedSides = board[idxHor] != EMPTY_CELL ? 1 : 0;
          if (!horOpenBegining) countClosedSides += 1;
          if (countClosedSides < 2) {
            openBothEnds = countClosedSides == 0;
            if (horLineCount == 2) {
              if (openBothEnds) {
                if (isLastRowI) pPosValue[idxHor] += semiOpen3cells;
                else pPosValue[idxHor] += open3cells;
                if ( (idxHor - 3) % row == 0) pPosValue[idxHor - 3] += semiOpen3cells;
                else pPosValue[idxHor - 3] += open3cells;
                accValue += open2cells;
              }
              else {
                if (cellIsOppo) {
                  if (countFriendlyPre > 4) pPosValue[idxHor - 3] += semiOpen3cells;
                } else if (isLastRowI) {
                  if (cellIsTeam) {
                    if (countFriendlyPre > 3) pPosValue[idxHor - 2] += semiOpen3cells;
                  }
                } else { // right side
                  cell4 = board[idxHor + 1];
                  cell5 = board[idxHor + 2];
                  // the whole 5-cell line fits
                  if ((idxHor / row == ((idxHor + 2) / row)) && (cell4 == 0 || cell4 == team) && (cell5 == 0 || cell5 == team)) {
                    pPosValue[idxHor] += semiOpen3cells;
                  }
                }
                accValue += semiOpen2cells;
              }
            }
            else if (horLineCount == 3) {
              if (openBothEnds) {
                if (isLastRowI) pPosValue[idxHor] += semiOpen4cells;
                else pPosValue[idxHor] += open4cells;
                if ((idxHor - 4) % row == 0) pPosValue[idxHor - 4] += semiOpen4cells;
                else pPosValue[idxHor - 4] += open4cells;
                accValue += open3cells;
              }
              else {
                if (cellIsOppo) {
                  if (countFriendlyPre > 4) pPosValue[idxHor - 4] += semiOpen4cells;
                }
                else if (isLastRowI) {
                  if (cellIsTeam) {
                    if (countFriendlyPre > 3) pPosValue[idxHor - 3] += semiOpen4cells;
                  }
                }
                else { 
                  cell5 = board[idxHor + 1];
                  if ((idxHor / row == ((idxHor + 1) / row)) && (cell5 == 0 || cell5 == team)) {
                    pPosValue[idxHor] += semiOpen4cells;
                  }
                }
                accValue += semiOpen2cells;
              }
            }
            else if (horLineCount == 4) {
              if (openBothEnds) {
                pPosValue[idxHor] += fiveInRow;
                pPosValue[idxHor - 5] += fiveInRow;
                accValue += open4cells;
              }
              else {
                if (cellIsOppo) {
                  if (countFriendlyPre > 4) pPosValue[idxHor - 5] += fiveInRow;
                }
                else {
                  pPosValue[idxHor] += fiveInRow;
                }

                accValue += semiOpen4row;
              }
            }
            else if (horLineCount == 5) {
              //pPosValue[idxHor] += fiveInRow;
              accValue += fiveInRow;
            }
          }
        }
      }
      // prep for next itteration
      if (!isLastRowI && board[idxHor] == team) {
        horLineCount += 1;
      }
      else {
        horOpenBegining = board[idxHor] == EMPTY_CELL;
        horLineCount = 0;
      }
      if (cellIsFree || cellIsTeam) countFriendlyPre += 1;
      else countFriendlyPre = 0;

      // ****************** vertical block *******************

      cellIsOppo = board[idxVer] != 0;

      // count vertical points
      if (verLineCount > 0 && (isLastRowI || board[idxVer] != team)) {
        if (isLastRowI && board[idxVer] == team) verLineCount += 1;
        if (verLineCount > 1) {
          countClosedSides = board[idxVer] != EMPTY_CELL ? 1 : 0;
          if (!verOpenBegining) countClosedSides += 1;
          if (countClosedSides < 2) {
            openBothEnds = countClosedSides == 0;
            if (verLineCount == 2) {
              if (openBothEnds) {
                if (isLastRowI) pPosValue[idxVer] += semiOpen3cells;
                else pPosValue[idxVer] += open3cells;
                if ( (idxVer - rowX3) / row == 0) pPosValue[idxVer - rowX3] += semiOpen3cells;
                else pPosValue[idxVer - rowX3] += open3cells;
                accValue += open2cells;
              }
              else {
                if(isLastRowI) pPosValue[idxVer - row - row] += semiOpen3cells;
                else if (cellIsOppo) pPosValue[idxVer - rowX3] += semiOpen3cells;
                else pPosValue[idxVer] += semiOpen3cells;
                accValue += semiOpen2cells;
              }
            }
            else if (verLineCount == 3) {
              if (openBothEnds) {
                if (isLastRowI) pPosValue[idxVer] += semiOpen4cells;
                else pPosValue[idxVer] += open4cells;
                if ((idxVer - rowX4) / row == 0) pPosValue[idxVer - rowX4] += semiOpen4cells;
                else pPosValue[idxVer - rowX4] += open4cells;
                accValue += open3cells;
              }
              else {
                if (isLastRowI) pPosValue[idxVer - rowX3] += semiOpen4cells;
                else if (cellIsOppo) pPosValue[idxVer - rowX4] += semiOpen4cells;
                else pPosValue[idxVer] += semiOpen4cells;
                accValue += semiOpen3cells;
              }
            }
            else if (verLineCount == 4) {
              if (openBothEnds) {
                pPosValue[idxVer] += fiveInRow;
                pPosValue[idxVer - rowX5] += fiveInRow;
                accValue += open4cells;
              }
              else {
                if (isLastRowI) pPosValue[idxVer - rowX4] += fiveInRow;
                else if (cellIsOppo) pPosValue[idxVer - rowX5] += fiveInRow;
                else pPosValue[idxVer] += fiveInRow;
                accValue += semiOpen4cells;
              }
            }
            else if (verLineCount == 5) {
              accValue += fiveInRow;
            }
          }
        }
      }
      // prep for next itteration
      if (!isLastRowI && board[idxVer] == team) {
        verLineCount += 1;
      }
      else {
        verOpenBegining = board[idxVer] == EMPTY_CELL;
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
    }
    else { // after stepping out of bottom of NxN we are gonna follow last row
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
          countClosedSides = board[idxFall] != EMPTY_CELL ? 1 : 0;
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
      }
      else {
        fallOpenBegining = board[idxFall] == EMPTY_CELL;
        fallLineCellCount = 0;
      }

      if (riseLineCellCount > 0 && (isLastRowI || board[idxRise] != team)) {
        if (isLastRowI && board[idxRise] == team) riseLineCellCount += 1;
        if (riseLineCellCount > 1) {
          countClosedSides = board[idxRise] != EMPTY_CELL ? 1 : 0;
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
      }
      else {
        riseOpenBegining = board[idxRise] == EMPTY_CELL;
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
