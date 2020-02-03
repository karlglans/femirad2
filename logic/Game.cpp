#include "Game.h"

Game::Game()
{
  ply = 0;
  gameOver = false;
}

Game::~Game()
{
}

int Game::getPly()
{
	return ply;
}

void Game::setPly(int ply)
{
  this->ply = ply;
}

bool Game::isOver()
{
  return gameOver;
}

void Game::setGameOver(bool isOver)
{
  gameOver = isOver;
}

bool Game::checkForWin(Board * board)
{
  gameOver = board->evaluateWin(1) || board->evaluateWin(2);
  return gameOver;
}

void Game::incPly()
{
  ply += 1;
}

int Game::getActingTeam() 
{
  return ply % 2 == 0 ? 1 : 2;
}
