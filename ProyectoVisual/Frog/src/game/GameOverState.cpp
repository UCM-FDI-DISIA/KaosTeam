#include "GameOverState.h"
#include "Game.h"
#include "../scenes/Menu.h"
#include "../scenes/MenuGameOver.h"
#include "RunningState.h"

GameOverState::GameOverState(): menu(new MenuGameOver(this, &sdlutils().images().at("BotonReintentar"/*Reintentar*/), //
				&sdlutils().images().at("BotonSalir"/*VolverMenuInicial*/))), //
				currScene(*menu) //
{}

GameOverState::~GameOverState() {
	delete menu;
	game = nullptr;
}

void GameOverState::leave() { //en este caso volveriamos a la pantalla de menu inicio
	Game::instance()->setNextState(Game::instance()->NEWGAME);
}

void GameOverState::update() {
	currScene.update();
}

void GameOverState::enter() { // -> Retry
	//Habria que resetear al player de alguna forma
	
	//Accedemos al runningState
	RunningState* runningState = dynamic_cast<RunningState*>(Game::instance()->getState(Game::RUNNING));

	//como running state tiene el puntero a la ultima escena, llamamos a resetGame desde alli
	if (runningState != nullptr) {
		runningState->resetGame();
	}

	//Cambiamos de estado
	Game::instance()->setNextState(Game::instance()->RUNNING);
}
