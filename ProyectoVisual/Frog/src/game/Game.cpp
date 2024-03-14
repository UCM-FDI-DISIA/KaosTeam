#include "Game.h"
#include "../scenes/RoomScene.h"

#include"../scenes/MenuInicio.h"
#include "../managers/DataManager.h"

#include "GameOverState.h"
#include "NewGameState.h"
#include "PausedState.h"
#include "RunningState.h"

//Constructor del game. Debe inicializar todos los elementos que se vayan a utilizar en todas las escenas.

Game::Game():
	imngr(im()), //
	previousState(nullptr),
	currentState(nullptr), //
	pausedState(nullptr), //
	newgameState(nullptr), //
	gameoverState(nullptr) {}

Game::~Game()
{
	delete hud;
	delete escenaActual;
	delete previousState;
	delete currentState;
	delete pausedState;
	delete newgameState;
	delete gameoverState;
}

void Game::init() {
	//Lanzar la escena de menu de inicio
	exit = false;
	SDLUtils::init(WIN_NAME, WIN_WIDTH, WIN_HEIGHT, "resources/config/menus.resources.json");
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 255);
	//escenaActual = new RoomScene(1);
	hud = new HUDManager(this, 9, 10, 0);

	newgameState = new NewGameState(this);
	currentState = newgameState;
	//paused_state_ = new PausedState(); //No esta terminado, mejor no llamarlo aun

	gameLoop();
}

void Game::gameLoop() {
	while (!exit) {
        DataManager::GetInstance()->UpdateFrameTime();
		escenaActual->update();
		render();
		imngr.PollEvents(); //Actualiza la entrada
		SDL_Event event;
		/*while (SDL_PollEvent(&event)) {
			escenaActual->HandleEvents(event);
		}*/
	}
}
/**
* Metodo general del renderizado, llama al Render como tal de la escena que est� actualmente en uso.
*/
void Game::render() {
	SDL_RenderClear(sdlutils().renderer());
	escenaActual->render();
	
	
	if(escenaActual->getCanRenderHUD())
		hud->render();
	
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
