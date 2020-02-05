#include "Search.h"
#include "GamestateNode.h"
#include "IndexGenerator.h"
#include "ranking.h"

SearchResult searchResult;
char actingPlayer;
char oppPlayer;

const int highValue = fiveInRow * 100;


int minmax(GamestateNode* const node, int depth, bool shouldMax, char plyPlayer, int alpha, int beta) {
  node->applyMoveToBoard(plyPlayer);  
  
  if (node->checkWin(plyPlayer)) {
    // will reward shortest path to win by adding depth
    node->value = plyPlayer == actingPlayer ? fiveInRow + depth : -fiveInRow;
    return node->value;
  }
  
  if (depth == 0) {
    node->value = node->getBoard()->evaluate(actingPlayer) -2 * node->getBoard()->evaluate(oppPlayer);
    return node->_move; // return node->_move;
  }

  char nextPlyPlayer = plyPlayer == 1 ? 2 : 1;
  GamestateNode* children = node->generateChildren(depth);
  int value;
  for (int i = 0; i < node->_nChildren; i++) {
    value = minmax(&children[i], depth - 1, !shouldMax, nextPlyPlayer, alpha, beta);
    if (shouldMax) alpha = (value > alpha) ? value : alpha; // max(value, alpha)
    else beta = (value < beta) ? value : beta; // min(value, beta)
    if (beta <= alpha) break;
  }

  // reached top node
  if (node->_move == -1) {
    GamestateNode* selection = GamestateNode::getBestChild(children, node->_nChildren, shouldMax);
    if (selection != 0) {
      searchResult.move = selection->_move;
      searchResult.value = selection->value;
    }
    return node->value;
  }

  const int bestValue = GamestateNode::getValueFromBestChild(children, node->_nChildren, shouldMax);
  delete[] children;
  node->value = bestValue;
  return node->value;
}

Search::Search(int depth)
  :depth(depth)
{
}

Search::~Search()
{
}

void Search::doSearch(SearchResult & sr, char actingPlayerStart, Board * board)
{
  // maybe move since it can be reused
  const int row = board->getRow();

  // maybe do this once in main
  IndexGenerator indexGen(row);
  GamestateNode::setIndexGenerator(&indexGen);
  GamestateNode::premadeIndecis = indexGen.getIndices(); // start from possible indecis

  // node0 is the current gameboard. It contains the move from previus player
  GamestateNode* node0 = new GamestateNode();
  node0->getBoard()->copyBoard(board);
  node0->setMove(-1); // the move is already written into the board

  const int depth = 5; // 3, 5, 7 seems to work

  searchResult.move = -2; // indicating no move found
  actingPlayer = actingPlayerStart;
  oppPlayer = actingPlayer == 1 ? 2 : 1;
  minmax(node0, depth, true, oppPlayer, -highValue, highValue);
  sr.move = searchResult.move;
  sr.value = searchResult.value;

  delete node0;
}
