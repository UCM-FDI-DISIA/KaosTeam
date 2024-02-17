#pragma once
/*
* Encargada de gestionar el HUD en el juego. Incluye los diálogos.
*/
#include "../sdlutils/Texture.h"

class Game;
class HUDManager
{
private:
	Game* game; //por ahora está aqui, aunq no sé para q se va a usar.
	int vidasActuales;
	int vidasMax;
	int xInicialFly = 15;
	int yInicial = 10;
	int xInicialWorm = 100;
	Texture* textFly;
	Texture* textWorm;
	SDL_Rect* rectFly;

public:
	HUDManager(Game*, int, int);

	void ChangeLives(int) {};

	void render();
	void update() {}; //por ahora no tiene nada
};



