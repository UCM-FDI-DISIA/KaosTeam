#include "Game.h"
#include "../scenes/RoomScene.h"

#include"../scenes/MenuInicio.h"
#include "../managers/DataManager.h"

#include "GameOverState.h"
#include "NewGameState.h"
#include "PausedState.h"
#include "RunningState.h"

//Constructor del game. Debe inicializar todos los elementos que se vayan a utilizar en todas las escenas.

Game::Game():current_state_(nullptr), //
paused_state_(nullptr), //
newgame_state_(nullptr), //
gameover_state_(nullptr) {}

Game::~Game()
{
	delete escenaActual;

	delete current_state_;
	delete paused_state_;
	delete newgame_state_;
	delete gameover_state_;

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

	newgame_state_ = new NewGameState();
	paused_state_ = new PausedState();

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

void Game::setScene(State s) //PROVISIONAL, NO FINAL
{
	switch (s) {
	case RUNNING:
		escenaActual = new RoomScene(1);
		break;
	case PAUSED:

		break;
	case NEWGAME:
		
		break;
	case GAMEOVER:
	
		break;
	default:
		break;
	}
}
