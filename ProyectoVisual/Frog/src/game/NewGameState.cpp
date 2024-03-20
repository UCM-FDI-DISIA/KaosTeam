#include "NewGameState.h"

#include "../scenes/MenuInicio.h"

NewGameState::NewGameState(Game* g): mStart(new MenuInicio(g, this)), currScene(*mStart), game(*g)
{
}

NewGameState::~NewGameState()
{
	delete mStart;
}

void NewGameState::leave()
{
	game.exitGame();
}

void NewGameState::update()
{
	currScene.update();
}

void NewGameState::enter()
{
	game.changeGameState(game.RUNNING);
}
