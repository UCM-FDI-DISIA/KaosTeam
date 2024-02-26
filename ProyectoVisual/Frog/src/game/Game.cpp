#include "Game.h"
#include "../scenes/MenuInicio.h"

//Constructor del game. Debe inicializar todos los elementos que se vayan a utilizar en todas las escenas.

Game::Game(){}

void Game::Init() {
	//Lanzar la escena de menu de inicio
	exit = false;
	SDLUtils::init(WIN_NAME, WIN_WIDTH, WIN_HEIGHT);
	//SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 255);
	escenaActual = new MenuInicio();
	HUD = new HUDManager(this, 9, 10);
	FollowPlayerComponent prueba = FollowPlayerComponent(0, 0);
	prueba.FollowPlayer(1, 2);
	prueba.FollowPlayer(2, 1);
	prueba.FollowPlayer(-1, -2);
	prueba.FollowPlayer(-2, -1);
	prueba.FollowPlayer(0, 1);
	prueba.FollowPlayer(1, 0);
	GameLoop();
}
void Game::GameLoop() {
	while (!exit) {
		escenaActual->Update();
		Render();
	}
}
/**
* Método general del renderizado, llama al Render como tal de la escena que esté actualmente en uso.
*/
void Game::Render() {
	SDL_RenderClear(sdlutils().renderer());
	escenaActual->Render();
	HUD->render();
	SDL_RenderPresent(sdlutils().renderer());
}