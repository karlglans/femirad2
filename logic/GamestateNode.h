#ifndef GAMESTATENODE
#define GAMESTATENODE

#include "common_types.h"
#include "Board.h"
#include "IndexGenerator.h"

class GamestateNode
{
  static IndexGenerator* indexGen;
public:
  static void setIndexGenerator(IndexGenerator* indexGen);
  //GamestateNode* parent;
  move _move;
  Board board;
  int value;
  short _nChildren;
  Board* getBoard();
  void setMove(move);
  void copyBoard(Board* board);
  void applyMoveToBoard(char actingPlayer);
  static int getValueFromBestChild(GamestateNode* nodes, int nNodes, bool max);
  static GamestateNode* getBestChild(GamestateNode* nodes, int nNodes, bool max);
  static short* premadeIndecis;
  GamestateNode* generateChildren(int depth);
  bool checkWin(int team);
  int generateChildMoves(int depth);

  GamestateNode();
  ~GamestateNode();
};
#endif
