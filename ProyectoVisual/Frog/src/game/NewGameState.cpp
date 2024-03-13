#include "NewGameState.h"

#include "../scenes/MenuInicio.h"

NewGameState::NewGameState(Game* game): mInicio(new MenuInicio(game))
{
}

NewGameState::~NewGameState()
{
}

void NewGameState::leave()
{
}

void NewGameState::update()
{
	mInicio->update();
}

void NewGameState::enter()
{
}
