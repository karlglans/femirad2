#include <algorithm>    // std::sort
#include <vector>       // std::vector

#include "IndexGenerator.h"

short * IndexGenerator::getIndices()
{
  return _indicesFromCentre;
}

IndexGenerator::IndexGenerator(int row): row(row)
{
  produceListOfIndecisFromCenter();
}

IndexGenerator::~IndexGenerator()
{
}

struct IndexAndDist {
  int pos;
  float distSqr;
};

struct less_than_dist {
  inline bool operator() (const IndexAndDist& struct1, const IndexAndDist& struct2) {
    return (struct1.distSqr < struct2.distSqr);
  }
};

/**
  * Will make an array of indecis from the middle of the NxN board and out.
  */
const short* IndexGenerator::produceListOfIndecisFromCenter()
{
  int size = row * row;
  std::vector<IndexAndDist> idxAndDist(size);
  const float centerPos = (row - 1) / 2.0;
  for (int index = 0, i = 0; i < row; i++) {
    for (int j = 0; j < row; j++, index++) {
      idxAndDist[index].distSqr = (i - centerPos) * (i - centerPos) + (j - centerPos) * (j - centerPos);
      idxAndDist[index].pos = index;
    }
  }
  std::sort(idxAndDist.begin(), idxAndDist.end(), less_than_dist());
  for (int i = 0; i < size; i++) {
    _indicesFromCentre[i] = idxAndDist[i].pos;
  }
  return _indicesFromCentre;
}

int IndexGenerator::pickFirstFreeIndexFromCentre(char* boardArr, const int row, short* result) {
  int size = row * row;
  for (int i = 0; i < size; i++) {
    if (boardArr[_indicesFromCentre[i]] == 0) {
      result[0] = _indicesFromCentre[i];
      return 1;
    }
  }
  return 0;
}


/**
* Looking for emty cells neighburing something. Will order indexis of thoe empty cells from inside to out.
*/

int IndexGenerator::makeInToOutSortedListOfSurroundingCells(char* boardArr, const int row, short* result) {
  const int size = row * row;
  int u, v, cell, cIdx, rIdx = 0;
  for (int i = 0; i < size; i++) {
    cIdx = _indicesFromCentre[i];
    cell = boardArr[cIdx];
    if (cell != 0) {
      continue;
    }

    u = cIdx % row;
    v = cIdx / row;

    // checking directions up/down/left/right
    if (u != 0 && boardArr[cIdx - 1] != 0) { // has a nighbure to left 
      goto addPos;
    }
    if (u != (row - 1) && boardArr[cIdx + 1] != 0) { // has a nighbure to right 
      goto addPos;
    }
    if (v != 0 && boardArr[cIdx - row] != 0) { // has a nighbure above 
      goto addPos;
    }
    if (v != (row - 1) && boardArr[cIdx + row] != 0) { // has a nighbure bellow 
      goto addPos;
    }


    if (u != 0 && v != 0 && boardArr[cIdx - row - 1] != 0) { // has a nighbure above left
      goto addPos;
    }
    if (u != (row - 1) && v != 0 && boardArr[cIdx - row + 1] != 0) { // has a nighbure above right
      goto addPos;
    }
    if (u != 0 && v != (row - 1) && boardArr[cIdx + row - 1] != 0) { // has a nighbure below left
      goto addPos;
    }
    else if (u != (row - 1) && v != (row - 1) && boardArr[cIdx + row + 1] != 0) { // has a nighbure below right
      goto addPos;
    }

    continue;

    addPos:
    result[rIdx] = cIdx;
    rIdx += 1;
  }

  return rIdx;
}


/**
 *   example of row 4 :
 *       --- u --->
 *    |   0  1  2  3
 *    v   4  5  6  7
 *    |   8  9  10 11
 *    V   12 13 14 15
 *
 *
 *  board[]:                       surroundingCells[]:
 *  0* 0* 0* 0* 0  0  0  0         0  1  2  3  -1 -1 -1 -1
 *  0* 1  1  0* 0  0  0  0         8  -1 -1 11 -1 -1 -1 -1
 *  0* 0* 1  0* 0  0  0  0         16 17 18 19 -1 -1 -1 -1
 *  0  0* 0* 0* 0  0  0  0   ==>   -1 25 26 27 -1 -1 -1 -1
 *  0  0  0  0  0  0  0  0         -1 -1 -1 -1 -1 -1 -1 -1
 *  0  0  0  0  0  0  0  0         -1 -1 -1 -1 -1 -1 -1 -1
 *  0  0  0  0  0  0  0* 0*        48 -1 -1 -1 -1 -1 54 55
 *  0  0  0  0  0  0  0* 2         -1 -1 -1 -1 -1 -1 62 -1
 *
 */

// not in use
void IndexGenerator::makeListOfSurroundingCells(char* boardArr, const int row, char* result) {
  const int isNotASurroundingCell = -1;
  int idx = 0;
  // iterates over each position decides if this position is neighbouring some taken cells
  for (int v = 0; v < row; v++) {
    for (int u = 0; u < row; u++, idx++) {
      if (boardArr[idx] != 0) {
        result[idx] = isNotASurroundingCell;
      }
      else {

        // checking directions up/down/left/right
        if (u != 0 && boardArr[idx - 1] != 0) {
          result[idx] = idx;
        }
        else if (u != (row - 1) && boardArr[idx + 1] != 0) {
          result[idx] = idx;
        }
        else if (v != 0 && boardArr[idx - row] != 0) {
          result[idx] = idx;
        }
        else if (v != (row - 1) && boardArr[idx + row] != 0) {
          result[idx] = idx;

          // diagonals
        }
        else if (u != 0 && v != 0 && boardArr[idx - row - 1] != 0) {
          result[idx] = idx;
        }
        else if (u != (row - 1) && v != 0 && boardArr[idx - row + 1] != 0) {
          result[idx] = idx;
        }
        else if (u != 0 && v != (row - 1) && boardArr[idx + row - 1] !=  0) {
          result[idx] = idx;
        }
        else if (u != (row - 1) && v != (row - 1) && boardArr[idx + row + 1] != 0) {
          result[idx] = idx;

        }
        else {
          result[idx] = isNotASurroundingCell;
        }
      }
    }
  }
}

