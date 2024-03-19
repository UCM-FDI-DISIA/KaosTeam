#pragma once
/*
* Encargada de gestionar el HUD en el juego. Incluye los diálogos.
*/
#include "../sdlutils/Texture.h"

class Game;

class HUDManager
{
private:
	Game& game; //por ahora está aqui, aunq no sé para q se va a usar.
	int vidasActuales, vidasMax, wormsActuales;
	int xInicialFly = 15;
	int yInicial = 10;
	int xInicialWorm = 700;
	Texture* textFly;
	Texture* textWorm;
	Texture* textNumWorms;
	SDL_Rect* rectFly;
	Font font = Font("resources/fonts/COMIC.ttf", 30);
	SDL_Color colorFont = {255, 255, 255, 255};
	/*static HUDManager* instance;*/
public:
	HUDManager( int, int, int);
	~HUDManager();
	
	//devuelve una isntancia del HUDManager y en caso de no haberla, crea una
	/*static HUDManager* GetInstance() {
		if (instance == nullptr) {
			instance = new HUDManager();
		}
		return instance;
	};*/

	void ChangeLives(int);
	void addWorms(int);

	void render();
	void update() {}; //por ahora no tiene nada
};



