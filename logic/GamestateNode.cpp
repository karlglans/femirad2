#include "GamestateNode.h"
#include "ranking.h"

IndexGenerator* GamestateNode::indexGen = 0;
short* GamestateNode::premadeIndecis = 0; // maybe guard better
const int MAX_CHIL = 10; // not in use

void GamestateNode::setIndexGenerator(IndexGenerator * indexGen)
{
  GamestateNode::indexGen = indexGen;
}

Board * GamestateNode::getBoard()
{
  return &board;
}

void GamestateNode::setMove(move move)
{
  _move = move;
}

void GamestateNode::copyBoard(Board * srcBoard)
{
  board.copyBoard(srcBoard);
}

void GamestateNode::applyMoveToBoard(char actingPlayer)
{
  if (_move != -1) {
    board.setCell(_move, actingPlayer);
  }
}

bool  GamestateNode::checkWin(int team) {
  return board.evaluateWin(team) >= fiveInRow;
}

int GamestateNode::getValueFromBestChild(GamestateNode* nodes, int nNodes, bool isMaximizing)
{
  // NOTE: maybe return ptr to node instead of just best value
  int bestVal = isMaximizing ? -10000 : 10000;
  if (nNodes == 0) {
    return -2;
  }
  else if(isMaximizing) {
    for (int n = 0; n < nNodes; n++) {
      if (nodes[n].value > bestVal) bestVal = nodes[n].value;
    }
  } else {
    for (int n = 0; n < nNodes; n++) {
      if (nodes[n].value < bestVal) bestVal = nodes[n].value;
    }
  }
  return bestVal;
}

GamestateNode * GamestateNode::getBestChild(GamestateNode * nodes, int nNodes, bool isMaximizing)
{
  // NOTE: maybe return ptr to node instead of just best value
  int bestVal = isMaximizing ? -10000 : 10000;
  int childIdx = -1;
  if (nNodes == 0) {
    return 0;
  }
  else if (isMaximizing) {
    for (int n = 0; n < nNodes; n++) {
      if (nodes[n].value > bestVal) {
        childIdx = n;
        bestVal = nodes[n].value;
      }
    }
  }
  else {
    for (int n = 0; n < nNodes; n++) {
      if (nodes[n].value < bestVal) {
        childIdx = n;
        bestVal = nodes[n].value;
      }
    }
  }
  if (childIdx == -1) return 0;
  return &nodes[childIdx];
}

short indexBuffer[BOARD_ROW * BOARD_ROW]; // internal buffer 

int GamestateNode::generateChildMoves(int depth) {
  const char* boardCells = board.getBoard();
  const int max_board_cells = board.getSize();
  //bool isTopLayer = _move == -1;

  int nChildren = GamestateNode::indexGen->makeInToOutSortedListOfSurroundingCells(
    (char*)boardCells, board.getRow(), indexBuffer);
  if (nChildren == 0) {
    nChildren = GamestateNode::indexGen->pickFirstFreeIndexFromCentre(
      (char*)boardCells, board.getRow(), indexBuffer);
  }
  if (nChildren != 0) {
    //GamestateNode::indexGen->moveGoodLookersBeginning(indexBuffer, nChildren, board.getGoodLookers());
  }

  // moveGoodLookersBegining
  return nChildren;

  //for (int cc = 0; cc < max_board_cells; cc++) {
  //  int nextIdx = premadeIndecis[cc];
  //  if (nChildren < MAX_CHIL && boardCells[nextIdx] == 0) {
  //    indexBuffer[nChildren] = nextIdx;
  //    nChildren++;
  //  }
  //}
  //return nChildren;
}

GamestateNode* GamestateNode::generateChildren(int depth)
{
  int nChildren = generateChildMoves(depth);
  GamestateNode* children = new GamestateNode[nChildren];
  for (int c = 0; c < nChildren; c++) {
    children[c].copyBoard(&board);
    children[c].setMove(indexBuffer[c]);
  }
  _nChildren = nChildren;
  return children;
}

GamestateNode::GamestateNode()
{
  _nChildren = -1;
}


GamestateNode::~GamestateNode()
{
}
