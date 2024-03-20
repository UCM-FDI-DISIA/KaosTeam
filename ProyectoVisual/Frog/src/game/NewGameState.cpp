#include "NewGameState.h"
#include "Game.h"
#include "../scenes/MenuInicio.h"

NewGameState::NewGameState(Game* g/*Game* game*/):game(g), mStart(new MenuInicio(g)), currScene(*mStart)
{
}

NewGameState::~NewGameState()
{
	delete mStart;
}

void NewGameState::leave()
{
}

void NewGameState::update()
{
	currScene.update();
}

void NewGameState::enter()
{
	game->changeGameState(game->RUNNING);
}
