#ifndef INDEX_GENERATOR
#define INDEX_GENERATOR

#include "BoardRow.h"

class IndexGenerator
{
private:
  short _indicesFromCentre[BOARD_ROW * BOARD_ROW];
  const int row;
public:
  short* getIndices();
  IndexGenerator(int row);
  int makeInToOutSortedListOfSurroundingCells(char* boardArr, const int row, short* result);
  int pickFirstFreeIndexFromCentre(char* boardArr, const int row, short* result);
  const short* produceListOfIndecisFromCenter();
  ~IndexGenerator();
};

#endif
