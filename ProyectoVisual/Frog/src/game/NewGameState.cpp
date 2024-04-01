#include "NewGameState.h"
#include "Game.h"
#include "../scenes/Menu.h"

NewGameState::NewGameState(Game* g): game(g), menu(new Menu(g, this, &sdlutils().images().at("BotonJuego"), 
				&sdlutils().images().at("BotonSalir"), INICIO)), currScene(*menu)
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
	game->changeGameState(game->RUNNING);
}
