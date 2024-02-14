#include "Game.h"
#include "../scenes/MenuInicio.h"

//Constructor del game. Debe inicializar todos los elementos que se vayan a utilizar en todas las escenas.

Game::Game() {}

void Game::Init() {
	//Lanzar la escena de menu de inicio
	exit = false;
	SDLUtils::init(WIN_NAME, WIN_WIDTH, WIN_HEIGHT);
	//SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 255);
	escenaActual = new MenuInicio();
	GameLoop();
}
void Game::GameLoop() {
	while (!exit) {
		escenaActual->Update();
		Render();
	}
}
/**
* M�todo general del renderizado, llama al Render como tal de la escena que est� actualmente en uso.
*/
void Game::Render() {
	SDL_RenderClear(sdlutils().renderer());
	escenaActual->Render();
	SDL_RenderPresent(sdlutils().renderer());
}