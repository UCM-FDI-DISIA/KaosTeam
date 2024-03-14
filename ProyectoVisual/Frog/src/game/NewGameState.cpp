#include "NewGameState.h"

#include "../scenes/MenuInicio.h"

NewGameState::NewGameState(Game* game): mStart(new MenuInicio(game)), currScene(*mStart)
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
}
