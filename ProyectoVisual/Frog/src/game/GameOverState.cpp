#include "GameOverState.h"
#include "Game.h"
#include "../scenes/Menu.h"
#include "../scenes/MenuGameOver.h"

GameOverState::GameOverState(Game* g): game(g), menu(new MenuGameOver(g, this, 
				&sdlutils().images().at("BotonJuego"/*Reintentar*/), //
				&sdlutils().images().at("BotonSalir"/*VolverMenuInicial*/))), //
				currScene(*menu) //
{}

GameOverState::~GameOverState() {
	delete menu;
	game = nullptr;
}

void GameOverState::leave() { //en este caso volveriamos a la pantalla de menu inicio
	game->setNextState(game->NEWGAME);
}

void GameOverState::update() {
	currScene.update();
}

void GameOverState::enter() { // -> Retry
	game->setNextState(game->RUNNING);
	//Habria que resetear al player de alguna forma
}
