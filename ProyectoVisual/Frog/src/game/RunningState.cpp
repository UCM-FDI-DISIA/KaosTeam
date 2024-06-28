#include "RunningState.h"
#include "../managers/InputManager.h"
#include "Game.h"
#include "../scenes/RoomScene.h"
#include "../sdlutils/SDLUtils.h"

RunningState::RunningState() : game(Game::instance()), hud(), currRoomScene(nullptr),
					currScene(nullptr), imngr(im())
{
}

RunningState::~RunningState()
{
	delete currScene;
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

	if (currRoomScene != nullptr)
	{
		currRoomScene->resetScene("resources/maps/niveles/nivel02/dentro/mapaN2_09_dentro.tmx");
	}
	else
	{
		currRoomScene = new RoomScene("resources/maps/niveles/pruebas/pruebas_Mauro.tmx");
		currScene = currRoomScene;
	}
	
	sdlutils().soundEffects().at("Flonk").play(-1, 0);

}
