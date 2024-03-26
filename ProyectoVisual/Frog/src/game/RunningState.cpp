#include "RunningState.h"

#include "../scenes/RoomScene.h"

RunningState::RunningState(Game* game) : hud(new HUDManager()), currScene(new RoomScene(1))
{
	allRooms.reserve(numRooms);
}

RunningState::~RunningState()
{
	for (auto a : allRooms)
	{
		delete a;
	}
	allRooms.clear();
}

void RunningState::leave()
{
}

void RunningState::update()
{
	currScene->update();
}

void RunningState::enter()
{
}

void RunningState::changeScene(int id)
{
	if (allRooms[id] == nullptr)
	{
		currScene = allRooms[id];
	}
	else
	{
		allRooms[id] = new RoomScene(id);
	}
 //Tenemos de encontrar una forma de entrar en nuevas habitaciones aquí

}
