#include "EndingState.h"
#include "Game.h"
#include "../scenes/MenuInicio.h"
#include"../scenes/EndingScene.h"

EndingState::EndingState():game(Game::instance()), ending(new EndingScene(this)), currScene(*ending)
{
}

EndingState::~EndingState()
{
	delete ending;
	game = nullptr;
}

void EndingState::leave()
{
	game->setNextState(game->NEWGAME);
}

void EndingState::update()
{
	currScene.update();
}

void EndingState::enter()
{
	ending->changeInitTime();
}
