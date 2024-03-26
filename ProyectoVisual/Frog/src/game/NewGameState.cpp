#include "NewGameState.h"
#include "Game.h"
#include "../scenes/Menu.h"

NewGameState::NewGameState(Game* g): game(g), mStart(new Menu(g, this, "../Frog/resources/Buttons/MenuJuego.png", "../Frog/resources/Buttons/MenuSalir.png", "background")), currScene(*mStart)
{
}

NewGameState::~NewGameState()
{
	delete mStart;
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
