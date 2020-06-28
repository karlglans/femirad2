#ifndef BOARD_EVALUATOR
#define BOARD_EVALUATOR
class Boardevaluator
{
  static const int free_cell = 0;
  static const int own_cell = 1;
  static const int oppo_cell = 2;
  static const int inaccessible = 3;
public:
  int calcCellLineValue(int* line);
  //int calcCellValue(int stepsDirPosi, int stepsDirNeg, int openPos, int openNeg);
  int evaluateBoard(const char* board, int* cellValues, int row, char team);
  int evaluateCell(short pos, const char* board, int row, char team);
  int sortCellValues(int* cellValues, short* cellIdx, int size, int maxValues);
  //bool stepDirection(int dir, int &pos, int &i, int &j, int row);
  Boardevaluator();
  ~Boardevaluator();
};
#endif
