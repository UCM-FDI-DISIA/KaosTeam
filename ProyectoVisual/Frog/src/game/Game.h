#pragma once
#include <SDL.h>
#include "../sdlutils/SDLUtils.h"
#include "../utils/Singleton.h"
#include "../ecs/Scene.h"
#include "../managers/HUDManager.h"


using namespace std;

using uint = unsigned int;
//Tamaños de ventana y otras configuraciones generales
constexpr uint WIN_WIDTH = 800;
constexpr uint WIN_HEIGHT = 600; 
const string WIN_NAME = "Flonk!";
constexpr uint NUM_BUNKER = 4;
constexpr uint WIN_CHANCE = 75;

/**
	El juego debería comenzar lanzando una escena de menu inicial en la que el jugador puede iniciar la partida.
*/
class Game
{
private:
	Scene* escenaActual;
	HUDManager* HUD;
	bool exit;

public:
	Game();
	void Init();
	void GameLoop();
	void Render();
};

