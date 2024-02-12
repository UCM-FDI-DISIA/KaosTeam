#pragma once
#include <SDL.h>
#include "../Scene.h"

using uint = unsigned int;
//Tamaños de ventana y otras configuraciones generales
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
	SDL_Window* window;
	SDL_Renderer* renderer;
	Scene* escenaActual;
	bool exit;

public:
	Game();
	void Init();
	void GameLoop();
	void Render();
};

