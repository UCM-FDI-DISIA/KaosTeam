#include "GameOverState.h"
#include "Game.h"
#include "../scenes/Menu.h"

GameOverState::GameOverState(Game* g): game(g), menu(new Menu(g, this, 
				&sdlutils().images().at("BotonJuego"/*Reintentar*/), //
				&sdlutils().images().at("BotonSalir"/*VolverMenuInicial*/), GAMEOVER)), //
				currScene(*menu) //
{}

GameOverState::~GameOverState()
{
	delete menu;
	game = nullptr;
}

void GameOverState::leave() //en este caso volveriamos a la pantalla de menu inicio
{
	game->setNextState(game->NEWGAME);
}

void GameOverState::update()
{
	currScene.update();
}

void GameOverState::enter()
{
	game->setNextState(game->NEWGAME);
}
