#include "Boardevaluator.h"
#include <assert.h>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include "ranking.h"


Boardevaluator::Boardevaluator(){}
Boardevaluator::~Boardevaluator(){}

// TODO: rework on this method. Combine for-loops
inline int Boardevaluator::calcCellLineValue(int* line) {
  int subLineValue = 0;
  int lineValue = 0;
  int s, o;
  int nHits = 0;
  for (s = 0; s < 5; s++) {
    subLineValue = 0;
    nHits = 0;
    for (o = 0; o < 5; o++) {
      int sum = s + o;
      if (line[sum] == oppo_cell || line[sum] == inaccessible) {
        subLineValue = 0;
        o = 5; // this 5 cells was useless
        continue;
      }
      if (line[s + o] == 0) {
        subLineValue += 1;
      } else {
        nHits += 3;
      }
    }
    if (nHits == 12) {
      subLineValue = fiveInRow;
    }
    else {
      subLineValue += (nHits * nHits);
    }
    lineValue += subLineValue;
  }
  // calc for opponent
  for (s = 0; s < 5; s++) {
    subLineValue = 0;
    nHits = 0;
    for (o = 0; o < 5; o++) {
      int sum = s + o;
      if (line[sum] == 1 || line[sum] == inaccessible) {
        subLineValue = 0;
        o = 5; // this 5 cells was useless
        continue;
      }
      if (line[s + o] == 0) {
        subLineValue += 1;
      }
      else {
        nHits += 3;  // 
      }
    }
    if (nHits == 12) {
      subLineValue = fiveInRow;
    }
    else {
      subLineValue += (nHits * nHits);
    }
    lineValue += subLineValue;
  }
  return lineValue;
}

const int max_steps = 6;
int debugit;

int line9[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, };

// the main purpose of this method is to put a value on each board position, that inicates how interesting this position is for
// a deeper search.
int Boardevaluator::evaluateBoard(const char* const board, int* const cellValues, const int row, const char team) {
  int i, j, ci, cj, dir;
  int step, pos, cpos = 0; // cpos: centrum position for ci-cj-loop.
  int cellvalue;
  int sum = 0;
  int rowX4 = row * 4;
  for (cj = 0; cj < row; cj++) {
    for (ci = 0; ci < row; ci++, cpos++) {
      cellvalue = 0;
      if (board[cpos] != free_cell) {
        cellValues[cpos] = 0;
        continue;
      }
      for (dir = 0; dir < 4; dir++) {
        // start positions:
        if (dir == 0) { pos = cpos - 4; i = ci - 4; j = cj; }
        else if (dir == 1) { pos = cpos + rowX4 - 4; i = ci - 4; j = cj + 4; }
        else if (dir == 2) { pos = cpos + rowX4; i = ci; j = cj + 4; }
        else if (dir == 3) { pos = cpos + rowX4 + 4; i = ci + 4; j = cj + 4; }
        for (step = 0; step < 9; step++) {
          if (i < 0 || i >= row || j < 0 || j >= row) {
            line9[step] = inaccessible;
          } else if (board[pos] == 0) line9[step] = 0;
          else line9[step] = board[pos] == team ? 1: 2;

          // next step
          if (dir == 0) { pos += 1; i += 1; }
          else if (dir == 1) { pos += 1; pos -= row; i += 1; j -= 1; }
          else if (dir == 2) { pos -= row; j -= 1; }
          else if (dir == 3) { pos -= 1; pos -= row; i -= 1; j -= 1; }
        }
        cellvalue += calcCellLineValue(line9);
      }
      cellValues[cpos] = cellvalue;
      sum += cellvalue;
    }
  }
  return sum;
}

// should value how good a move is for team
int Boardevaluator::evaluateCell(const short cpos, const char* board, const int row, const char team) {
  int i, j, ci, cj, dir;
  int step, pos;
  int cellvalue = 0;
  int rowX4 = row * 4;
  ci = cpos % row;
  cj = cpos / row;
  for (dir = 0; dir < 4; dir++) {
    // start positions:
    if (dir == 0) { pos = cpos - 4; i = ci - 4; j = cj; }
    else if (dir == 1) { pos = cpos + rowX4 - 4; i = ci - 4; j = cj + 4; }
    else if (dir == 2) { pos = cpos + rowX4; i = ci; j = cj + 4; }
    else if (dir == 3) { pos = cpos + rowX4 + 4; i = ci + 4; j = cj + 4; }
    for (step = 0; step < 9; step++) {
      if (i < 0 || i >= row || j < 0 || j >= row) {
        line9[step] = inaccessible;
      }
      else if (board[pos] == free_cell) line9[step] = free_cell;
      else line9[step] = board[pos] == team ? own_cell : oppo_cell;

      // next step
      if (dir == 0) { pos += 1; i += 1; }
      else if (dir == 1) { pos += 1; pos -= row; i += 1; j -= 1; }
      else if (dir == 2) { pos -= row; j -= 1; }
      else if (dir == 3) { pos -= 1; pos -= row; i -= 1; j -= 1; }
    }
    cellvalue += calcCellLineValue(line9);
  }
  return cellvalue;
}

struct IndexAndValue {
  int pos;
  int value;
};

struct less_than_dist {
  inline bool operator() (const IndexAndValue& struct1, const IndexAndValue& struct2) {
    return (struct1.value > struct2.value);
  }
};

int Boardevaluator::sortCellValues(int* cellValues, short* cellIdx, const int size, const int maxValues) {
  int nGoodValues = 0;
  const int threshold = 0;
  std::vector<IndexAndValue> idxAndDist(size);
  for (int i = 0; i < size; i++) {
    idxAndDist[i].value = cellValues[i];
    idxAndDist[i].pos = i;
    if (cellValues[i] > threshold) {
      nGoodValues += 1;
    }
  }
  int nPotetialValues = 0;
  std::sort(idxAndDist.begin(), idxAndDist.end(), less_than_dist());
  for (int i = 0; i < size; i++) {
    if (i > maxValues) {
      i = size;
      continue;
    }
    nPotetialValues++;
    cellIdx[i] = idxAndDist[i].pos;
  }
  return nPotetialValues;
}

