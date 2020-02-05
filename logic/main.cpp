#include "config.h"
#ifdef USE_EMSCRIPTEN
#include <emscripten.h>
#endif

#include "BoardRow.h"
#include "Board.h"
#include "Game.h"
#include "IndexGenerator.h"
#include "Search.h"

Game* game = nullptr;
Board* board = nullptr;
IndexGenerator* idxGen = nullptr;

int main() {
  idxGen = new IndexGenerator(BOARD_ROW);
  game = new Game();
  board = new Board();
  board->clean();
  //board->setCell(120, 1);
  //board->setCell(135, 2);
  //board->setCell(119, 1);
  //board->setCell(136, 2);
  //board->setCell(103, 1);
  //board->setCell(137, 2);
  //board->setCell(138, 1);
  //board->setCell(151, 2);
  //board->setCell(121, 1);
  //board->setCell(118, 2);
  //game->setPly(10);
  // should give 108 or 106




  //board->setCell(136, 1);
  //board->setCell(135, 2);
  //game->setPly(4);
  #ifdef USE_EMSCRIPTEN
	EM_ASM_({
	    console.log("main() done v22, row:", $0);
	}, BOARD_ROW);
#endif
	return 0;
}

extern "C" void releaseApp() {
  delete game;
  delete board;
#ifdef USE_EMSCRIPTEN
  EM_ASM_({
	    console.log("releaseApp() done");
	});
#endif
}

extern "C" int doNextMove(int depth, char* board_ptr) {
#ifdef USE_EMSCRIPTEN
  EM_ASM_({
      console.log("doNextMove() start");
    });
#endif
  if (game->isOver()) {
#ifdef USE_EMSCRIPTEN
    EM_ASM_({
        console.log("doNextMove() gameover");
      });
#endif
    return 1;
  }
  Search search(depth);
  SearchResult sr;
  const int actingPlayer = game->getActingTeam();
  search.doSearch(sr, actingPlayer, board);
  if (!board->isValidMove(sr.move)) return -1;
  board->setCell(sr.move, actingPlayer); 
  //board_ptr[sr.move] = game->getActingTeam();
  board->copyBoard(board_ptr); // later on just use row above
  game->incPly();
#ifdef USE_EMSCRIPTEN
  EM_ASM_({
      console.log("doNextMove() acting:", $0, "move:", $1, $2);
    }, actingPlayer, sr.move, sr.value);
#endif
  return game->checkForWin(board) ? 0 : 1;
}

extern "C" int startNewGame() {
	game = new Game();
  
	return 0;
}

extern "C" int markEmptyCell(char* board_ptr, int cellIdx) {
  if (game->isOver()) return 0;
  if (board->isValidMove(cellIdx)) {
    board_ptr[cellIdx] = game->getActingTeam();
    const int actingPlayer = game->getActingTeam();
    board->setCell(cellIdx, actingPlayer);
    game->incPly();
    return game->checkForWin(board) ? 0 : 1;
  }
	return -1;
}