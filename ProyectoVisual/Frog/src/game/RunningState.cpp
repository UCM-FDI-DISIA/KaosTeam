#include "RunningState.h"
#include "../managers/InputManager.h"
#include "Game.h"
#include "../scenes/RoomScene.h"


RunningState::RunningState() : hud(), currScene(new RoomScene("resources/maps/niveles/nivel01/mapaN1_03.tmx")), imngr(im()) {
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
	if (imngr.getEscape()) {
		Game::instance()->setNextState(Game::instance()->PAUSED);
	}

	//currScene->update();
}

void RunningState::enter() {
}

void RunningState::changeScene(int id) {/*
	if (allRooms[id] == nullptr)
	{
		currScene = allRooms[id];
	}
	else
	{
		allRooms[id] = new RoomScene(id);
	}*/
	//Tenemos de encontrar una forma de entrar en nuevas habitaciones aqui
}
