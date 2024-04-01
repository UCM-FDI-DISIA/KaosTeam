#include "Game.h"
#include "../scenes/RoomScene.h"

#include"../scenes/MenuInicio.h"
#include "../managers/DataManager.h"

//Constructor del game. Debe inicializar todos los elementos que se vayan a utilizar en todas las escenas.

Game::Game(){}

Game::~Game()
{
	delete escenaActual;
	delete HUD;
	//Al actuar como singleton, no creo que haya que eliminar inputManager (existe durante toda la duración del programa)
}

void Game::init() {
	//Lanzar la escena de menu de inicio
	exit = false;
	SDLUtils::init(WIN_NAME, WIN_WIDTH, WIN_HEIGHT);
    inputManager = InputManager::GetInstance();
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 255);
	escenaActual = new RoomScene(1);
	HUD = new HUDManager(this, 9, 10, 0);
	escenaActual = new MenuInicio(this);
	gameLoop();

}

void Game::gameLoop() {
	while (!exit) {
        DataManager::GetInstance()->UpdateFrameTime();
		escenaActual->update();
		render();
		inputManager->PollEvents(); //Actualiza la entrada
		SDL_Event event;
		/*while (SDL_PollEvent(&event)) {
			escenaActual->HandleEvents(event);
		}*/
	}
}
/**
* M�todo general del renderizado, llama al Render como tal de la escena que est� actualmente en uso.
*/
void Game::render() {
	SDL_RenderClear(sdlutils().renderer());
	escenaActual->render();
	
	if(escenaActual->getCanRenderHUD())
		HUD->render();
	
	SDL_RenderPresent(sdlutils().renderer());
}

void Game::exitGame()
{
	exit = true;
}

void Game::changeScene() //PROVISIONAL, NO FINAL
{
	escenaActual = new RoomScene(1);
}
