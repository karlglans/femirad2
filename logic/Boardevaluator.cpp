#include "Boardevaluator.h"
#include <assert.h>
#include "ranking.h"


Boardevaluator::Boardevaluator()
{
}


Boardevaluator::~Boardevaluator()
{
}

// spaceDir1 : space including stepsDir1
int Boardevaluator::calcCellValue(int stepsDir1, int stepsDir2, int spaceDir1, int spaceDir2) {
  bool dir1Open = spaceDir1 > stepsDir1;
  bool dir2Open = spaceDir2 > stepsDir2;
  if (stepsDir1 > spaceDir1) spaceDir1 = stepsDir1;
  if (stepsDir2 > spaceDir2) spaceDir2 = stepsDir2;
  int nOpen = (dir1Open ? 1 : 0) + (dir2Open ? 1 : 0);
  int steps = stepsDir1 + stepsDir2 + 1;
  int space = spaceDir1 + spaceDir2 + 1;
  if (space < 5) return 0; // worthless
  if (steps == 5) return fiveInRow;
  if (nOpen == 2) {
    if (steps == 4) return open4cells;
    else if (steps == 3) return open3cells;
    else if (steps == 2) return open2cells;
  } else {
    if (steps == 4) return semiOpen4cells;
    else if (steps == 3) return semiOpen3cells;
    else if (steps == 2) return semiOpen2cells;
  }
  return 0;
}

const int max_steps = 6;
int debugit;

inline bool Boardevaluator::stepDirection(const int dir, int &pos, int &i, int &j, const int row) {
  if (dir == 0) { pos += 1; i += 1; }
  else if (dir == 1) { pos += 1; pos -= row; i += 1; j -= 1; }
  else if (dir == 2) { pos -= row; j -= 1; }
  else if (dir == 3) { pos -= 1; pos -= row; i -= 1; j -= 1; }
  else if (dir == 4) { pos -= 1; i -= 1; }
  else if (dir == 5) { pos -= 1; pos += row; i -= 1; j += 1; }
  else if (dir == 6) { pos += row; j += 1; }
  else if (dir == 7) { pos += 1; pos += row; i += 1; j += 1; }
  if (i >= row || j >= row || i < 0 || j < 0) {
    return false;
  }
  return true;
}

int Boardevaluator::evaluate(const char* const board, int* const cellValues, const int row, const char team) {
  int i, j, ci, cj, dir; // 
  int steps, pos, cpos = 0; // cpos: centrum position for ci-cj-loop.
  int cSteps;
  int closedInDir[] = { 0, 0, 0, 0, 0, 0, 0, 0 }; // how meny steps can be taken before stop
  int stepsDir[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  bool hasValueInDirection[] = { false, false, false, false, false, false, false, false };
  bool cellHasValue, directionHasValue;
  int cellValue = 0;
  for (cj = 0; cj < row; cj++) {
    for (ci = 0; ci < row; ci++, cpos++) {
      if (cpos == 34) {
        debugit = 0;
      }
      if (board[cpos] != 0) {
        cellValues[cpos] = 0;
        continue;
      }
      cellHasValue = false;
      // first step in all directions
      for (dir = 0; dir < 8; dir++) {
        pos = cpos; i = ci; j = cj;
        closedInDir[dir] = 0; stepsDir[dir] = 0; // reset
        hasValueInDirection[dir] = false;
        if (!stepDirection(dir, pos, i, j, row)) continue;
        if (board[pos] == team) {
          stepsDir[dir] = 1;
          closedInDir[dir] = 1;
          hasValueInDirection[dir] = true;
          cellHasValue = true;
        } else if (board[pos] == 0) closedInDir[dir] = 1;  // at least 1 step in this dir is possible
      }
      if (!cellHasValue) continue;
      for (dir = 0; dir < 8; dir++) {
        if (hasValueInDirection[dir]) hasValueInDirection[(dir + 4) % 8] = true;
      }
      // keep looking in prommesing directions
      for (dir = 0; dir < 8; dir++) {
        if (!hasValueInDirection[dir]) continue;
        pos = cpos; i = ci; j = cj;
        for (steps = 1; steps < max_steps; steps++) {
          if (!stepDirection(dir, pos, i, j, row)) {
            closedInDir[dir] = steps - 1; // this step was not allowed
            steps = max_steps;
            continue;
          }
          if (steps == 1) continue; // step 1 is just for seting pos, i, j
          if (board[pos] == team) {
            stepsDir[dir] = steps;
          } else {
            if (board[pos] == 0) {
              closedInDir[dir] = steps; // incrementing closing. but slow
            } else { // opponent
              closedInDir[dir] = steps - 1;
              steps = max_steps;
            }
          }
        }
      }
      cellValues[cpos] = 0;
      if (!cellHasValue) continue;
      cellValue = calcCellValue(stepsDir[0], stepsDir[4], closedInDir[0], closedInDir[4]);
      cellValue += calcCellValue(stepsDir[1], stepsDir[5], closedInDir[1], closedInDir[5]);
      cellValue += calcCellValue(stepsDir[2], stepsDir[6], closedInDir[2], closedInDir[6]);
      cellValue += calcCellValue(stepsDir[3], stepsDir[7], closedInDir[3], closedInDir[7]);
      cellValues[cpos] = cellValue;
    }
  }

  return 0;
}
