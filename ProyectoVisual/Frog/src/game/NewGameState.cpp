#include "NewGameState.h"
#include "Game.h"
#include "../scenes/MenuInicio.h"
#include "RunningState.h"
#include"../scenes/EndingScene.h"

NewGameState::NewGameState(Game* g) : game(g), menu(new MenuInicio(g, this, &sdlutils().images().at("BotonJuego"),
	&sdlutils().images().at("BotonSalir"))), currScene(*menu)
{
}

NewGameState::~NewGameState()
{
	delete menu;
	game = nullptr;
}

void NewGameState::leave()
{
	Game::instance()->exitGame();
}

void NewGameState::update()
{
	currScene.update();
}

void NewGameState::enter()
{
	//Accedemos al runningState
	RunningState* runningState = dynamic_cast<RunningState*>(Game::instance()->getState(Game::RUNNING));

	//como running state tiene el puntero a la escena de juego, hacemos que inicialice un nuevo juego desde ah�
	if (runningState != nullptr) {
		runningState->createNewGame();
	}

	Game::instance()->setNextState(Game::instance()->RUNNING);
}
