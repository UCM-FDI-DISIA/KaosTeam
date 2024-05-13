#include "RunningState.h"
#include "../managers/InputManager.h"
#include "Game.h"
#include "../scenes/RoomScene.h"

RunningState::RunningState(Game* g) : game(g), hud(), currScene(new RoomScene(1)),imngr(im())
{
}

RunningState::~RunningState()
{
	delete currScene;
}

void RunningState::leave()
{
}

void RunningState::update()
{
	currScene->update();
	if (imngr.getEscape())
	{
		game->setNextState(game->PAUSED);
	}
	//currScene->update();
}

void RunningState::enter()
{
}
