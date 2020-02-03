#pragma once
#include "Board.h"

class Game
{
	int ply;
  bool gameOver;
public:
	Game();
	~Game();
	int getActingTeam();
	void incPly();
	int getPly();
  void setPly(int ply);
  bool isOver();
  void setGameOver(bool isOver);
  bool checkForWin(Board* board);
};

