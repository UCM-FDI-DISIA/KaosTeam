#include "GameOverState.h"
#include "Game.h"
#include "../scenes/Menu.h"
#include "../scenes/MenuGameOver.h"

GameOverState::GameOverState(): menu(new MenuGameOver(Game::instance(), this,
				&sdlutils().images().at("BotonJuego"/*Reintentar*/), //
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
	Game::instance()->setNextState(Game::instance()->RUNNING);
	//Habria que resetear al player de alguna forma
}
