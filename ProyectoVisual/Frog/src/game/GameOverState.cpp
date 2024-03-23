#include "GameOverState.h"
#include "Game.h"
#include "../scenes/Menu.h"

GameOverState::GameOverState(Game* g):game(g),mGameOver(new Menu(game, this, "", "", "")), currScene(*mGameOver)
{
}

GameOverState::~GameOverState()
{
	delete mGameOver;
}

void GameOverState::leave() //en este caso volveriamos a la pantalla de menu inicio
{
	game->changeGameState(game->NEWGAME);
}

void GameOverState::update()
{
	currScene.update();
}

void GameOverState::enter()
{
	game->changeGameState(game->NEWGAME);
}
