#include "RunningState.h"
#include "../managers/InputManager.h"
#include "Game.h"
#include "../scenes/RoomScene.h"
#include "../sdlutils/SDLUtils.h"


RunningState::RunningState() : currRoomScene(nullptr), currScene(nullptr), hud(), imngr(im()) {
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

void RunningState::leave() {
}

void RunningState::update() {
	currScene->update();
	if (imngr.getEscape()) {
		sdlutils().soundEffects().at("Flonk").pauseChannel();
		Game::instance()->setNextState(Game::instance()->PAUSED);
	}

	if (currRoomScene->getGameOverState()) {
		sdlutils().soundEffects().at("Flonk").pauseChannel();
		Game::instance()->setNextState(Game::instance()->GAMEOVER);
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

void RunningState::resetGame() {
	//revivimos al jugador
	currRoomScene->revivePlayer();
	sdlutils().soundEffects().at("Flonk").play(-1, 0);
}

void RunningState::createNewGame() {
	delete currRoomScene;
	currRoomScene = new RoomScene("resources/maps/niveles/nivel02/dentro/mapaN2_09_dentro.tmx");
	currScene = currRoomScene;
	sdlutils().soundEffects().at("Flonk").play(-1, 0);
}
