#pragma once
#include <SDL.h>
#include<list>
#include "../sdlutils/SDLUtils.h"
#include "../utils/Singleton.h"
#include "GameState.h"
#include"../sdlutils/checkML.h"

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
	list<GameState*> updateStates;
	list<GameState*> renderStates;
	GameState* pausedState;
	GameState* runningState;
	GameState* newgameState;
	GameState* gameOverState;

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

	void changeGameState(State s);
	void exitGame();
};
