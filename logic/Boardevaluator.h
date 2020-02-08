#ifndef BOARD_EVALUATOR
#define BOARD_EVALUATOR
class Boardevaluator
{
public:
  int calcCellValue(int stepsDirPosi, int stepsDirNeg, int openPos, int openNeg);
  int evaluate(const char* board, int* cellValues, int row, char team);
  bool stepDirection(int dir, int &pos, int &i, int &j, int row);
  Boardevaluator();
  ~Boardevaluator();
};
#endif
