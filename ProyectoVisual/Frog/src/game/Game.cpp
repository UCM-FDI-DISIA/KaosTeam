#include "Game.h"
#include "../MenuInicio.h"

//Constructor del game. Debe inicializar todos los elementos que se vayan a utilizar en todas las escenas.

Game::Game() {
	window = SDL_CreateWindow("juego", 100, 200, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
void Game::Init() {
	//Lanzar la escena de menu de inicio
	exit = false;
	window = SDL_CreateWindow("juego", 100, 200, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 100, 255, 100, 255);
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
* Método general del renderizado, llama al Render como tal de la escena que esté actualmente en uso.
*/
void Game::Render() {
	SDL_RenderClear(renderer);
	escenaActual->Render();
	SDL_RenderPresent(renderer);
}