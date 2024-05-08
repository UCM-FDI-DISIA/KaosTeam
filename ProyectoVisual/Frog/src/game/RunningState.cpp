#include "RunningState.h"
#include "../managers/InputManager.h"
#include "Game.h"
#include "../scenes/RoomScene.h"


RunningState::RunningState(Game* g) : game(g), hud(), currScene(new RoomScene("resources/maps/niveles/nivel03/mapaN3_01.tmx")),imngr(im())
{
	//allRooms.reserve(numRooms);
}

RunningState::~RunningState()
{
	delete currScene;
	//for (auto a : allRooms)
	//{
	//	delete a;
	//}
	//allRooms.clear();
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

void RunningState::changeScene(int id)
{/*
	if (allRooms[id] == nullptr)
	{
		currScene = allRooms[id];
	}
	else
	{
		allRooms[id] = new RoomScene(id);
	}*/
 //Tenemos de encontrar una forma de entrar en nuevas habitaciones aqu�

}
