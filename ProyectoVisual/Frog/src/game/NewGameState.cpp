#include "NewGameState.h"
#include "Game.h"
#include "../scenes/MenuInicio.h"

NewGameState::NewGameState(): menu(new MenuInicio(Game::instance(), this,
				&sdlutils().images().at("BotonJuego"), 
				&sdlutils().images().at("BotonSalir"))),
				currScene(*menu)
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
	Game::instance()->setNextState(Game::instance()->RUNNING);
}
