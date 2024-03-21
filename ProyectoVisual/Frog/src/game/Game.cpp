#include "Game.h"

#include "../managers/InputManager.h"
#include "../scenes/RoomScene.h"

#include"../scenes/MenuInicio.h"
#include "../managers/DataManager.h"

#include "GameOverState.h"
#include "NewGameState.h"
#include "PausedState.h"
#include "RunningState.h"

//Constructor del game. Debe inicializar todos los elementos que se vayan a utilizar en todas las escenas.

Game::Game(): //
	pausedState(nullptr), //
	newgameState(nullptr), //
	gameOverState(nullptr) {}

Game::~Game()
{
	delete pausedState;
	delete newgameState;
	delete gameOverState;
}

void Game::init() {
	//Lanzar la escena de menu de inicio
	exit = false;
	SDLUtils::init(WIN_NAME, WIN_WIDTH, WIN_HEIGHT, "../resources/config/menus.resources.json");
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 255);
	//escenaActual = new RoomScene(1);

	newgameState = new NewGameState(this);
	runningState = new RunningState(this);
	//pausedState = new PausedState();
	renderStates.push_front(newgameState);
	updateStates.push_front(newgameState);
	//paused_state_ = new PausedState(); //No esta terminado, mejor no llamarlo aun

	gameLoop();
}

void Game::gameLoop() {
	SDL_Event event;
	auto& imngr = im();

	while (!exit) {
        DataManager::GetInstance()->UpdateFrameTime();

		for (auto a : updateStates)
			a->getScene()->update();

		render();
		imngr.PollEvents(); //Actualiza la entrada
		
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

	for (auto a : renderStates)
	{
		a->getScene()->render();
	}

	//Esto se realiza en cada escena
	/*if (currentState->getScene()->getCanRenderHUD())
		hud->render();*/
	
	SDL_RenderPresent(sdlutils().renderer());
}

void Game::exitGame()
{
	exit = true;
}


//Cambiar a metodo para cambiar de estado (newgame, running, pause, gameover)
void Game::changeGameState(State s) //PROVISIONAL, NO FINAL
{
	switch (s) {
	case RUNNING:
		updateStates.clear();
		renderStates.clear();
		updateStates.push_front(runningState);
		renderStates.push_front(runningState);
		break;
	case PAUSED:
		updateStates.clear();
		updateStates.push_front(pausedState);
		renderStates.push_front(pausedState);
		break;
	case NEWGAME:
		updateStates.clear();
		renderStates.clear();
		updateStates.push_front(newgameState);
		renderStates.push_front(newgameState);
		break;
	case GAMEOVER:
		updateStates.clear();
		renderStates.clear();
		updateStates.push_front(gameOverState);
		renderStates.push_front(gameOverState);
		break;
	default:
		break;
	}
}
