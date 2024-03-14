#pragma once
#include <SDL.h>
#include "../sdlutils/SDLUtils.h"
#include "../utils/Singleton.h"
#include "../ecs/Scene.h"
#include "../managers/HUDManager.h"
#include "../managers/InputManager.h"
#include "GameState.h"

using namespace std;

using uint = unsigned int;
//Tamaños de ventana y otras configuraciones generales
const string WIN_NAME = "Flonk!";
constexpr uint WIN_WIDTH = 800;
constexpr uint WIN_HEIGHT = 600;
constexpr uint NUM_BUNKER = 4;
constexpr uint WIN_CHANCE = 75;

/**
	El juego debería comenzar lanzando una escena de menu inicial en la que el jugador puede iniciar la partida.
*/
class Game
{
private:
	Scene* escenaActual;
	HUDManager* hud;
	InputManager& imngr;

	GameState* previousState;
	GameState* currentState;
	GameState* pausedState;
	GameState* runningState;
	GameState* newgameState;
	GameState* gameoverState;

	bool exit;

public:
	enum State {
		RUNNING, PAUSED, NEWGAME, GAMEOVER
	};
	Game();
	~Game();
	void init();
	void gameLoop();
	void render();
	void exitGame();
    void setScene(State s);
};

