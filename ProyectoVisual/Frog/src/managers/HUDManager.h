#pragma once
/*
* Encargada de gestionar el HUD en el juego. Incluye los di�logos.
*/
#include "../sdlutils/Texture.h"

class Game;
class HUDManager
{
private:
	Game* game; //por ahora est� aqui, aunq no s� para q se va a usar.
	int vidasActuales;
	int vidasMax;
	int xInicial = 15;
	int yInicial = 10;
	Texture* text;
	SDL_Rect* rect;

public:
	HUDManager(Game*, int, int);

	void ChangeLives(int) {};

	void render();
	void update() {}; //por ahora no tiene nada
};



