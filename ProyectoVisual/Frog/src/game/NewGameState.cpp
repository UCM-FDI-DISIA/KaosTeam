#include "NewGameState.h"
#include "Game.h"
#include "../scenes/MenuInicio.h"

NewGameState::NewGameState(Game* g): game(g), mStart(new MenuInicio(g, this)), currScene(*mStart)
{
}

NewGameState::~NewGameState()
{
	delete mStart;
}

void NewGameState::leave()
{
	game->exitGame();
}

void NewGameState::update()
{
	currScene.update();
}

void NewGameState::enter()
{
	game->changeGameState(game->RUNNING);
}
