#include "GameOverState.h"
#include "Game.h"
#include "../scenes/Menu.h"

GameOverState::GameOverState(Game* g):game(g), menu(new Menu(g, this, &sdlutils().images().at("Reintentar"),
	&sdlutils().images().at("VolverMenuInicial"), GAMEOVER)), currScene(*menu)
{
}

GameOverState::~GameOverState()
{
	delete menu;
}

void GameOverState::leave() //en este caso volveriamos a la pantalla de menu inicio
{
	game->changeGameState(game->NEWGAME);
}

void GameOverState::update()
{
	currScene.update();
}

void GameOverState::enter()
{
	game->changeGameState(game->NEWGAME);
}
