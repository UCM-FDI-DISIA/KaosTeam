#include "NewGameState.h"
#include "Game.h"
#include "../scenes/MenuInicio.h"

NewGameState::NewGameState(Game* g): game(g), menu(new MenuInicio(g, this, &sdlutils().images().at("BotonJuego"), 
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
	game->exitGame();
}

void NewGameState::update()
{
	currScene.update();
}

void NewGameState::enter()
{
	game->setNextState(game->RUNNING);
}
