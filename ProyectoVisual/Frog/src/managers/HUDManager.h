#pragma once
/*
* Encargada de gestionar el HUD en el juego. Incluye los diálogos.
*/
#include "../sdlutils/Texture.h"
#include "../utils/Singleton.h"

class Game;

class HUDManager: public Singleton<HUDManager>
{
	friend Singleton<HUDManager>;

private:
	Game* game; //por ahora está aqui, aunq no sé para q se va a usar.

	int vidasActuales, vidasMax, wormsActuales;
	int xInicialFly = 15;
	int yInicial = 10;
	int xInicialWorm = 700;
	Texture* textFly;
	Texture* textWorm;
	Texture* textNumWorms;
	//Texture texNumWormsNuevo;
	SDL_Rect rectFly;
	Font* font;
	SDL_Color colorFont = {255, 255, 255, 255};

	//Constructora
	HUDManager();
    
public:
	
	//Destructora
	virtual ~HUDManager(); 
	
	////Gestion para hacer singleton de HUDManager
	//HUDManager(HUDManager&) = delete;
	//void operator=(const HUDManager&) = delete;
	//static HUDManager* GetInstance() {
	//	if (instance == nullptr) {
	//		instance = new HUDManager();
	//	}
	//	return instance;
	//};

	void ChangeLives(int);
	void ChangeMaxLife(int);
	void addWorms(int);

	void render();
	void update() {}; //por ahora no tiene nada
};
//inline HUDManager& hud() {
//	return *HUDManager::GetInstance();
//}


