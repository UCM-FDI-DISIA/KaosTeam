#pragma once
/*
* Encargada de gestionar el HUD en el juego. Incluye los diálogos.
*/
#include "../sdlutils/Texture.h"
#include "../utils/Singleton.h"
#include "../components/LifeComponent.h"

class Game;

class HUDManager: public Singleton<HUDManager>
{
	friend Singleton<HUDManager>;

private:
	Game* game; //por ahora está aqui, aunq no sé para q se va a usar.
	int vidasActuales, vidasMax;
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
	LifeComponent* lives;
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
	
	void LinkLives(LifeComponent* playerLife); //Metodo para acceder a las vidas del jugador
	void ChangeLives(int);
	void ChangeMaxLife(int);
	void setWorms(int);

	void render();
	void update(); //por ahora no tiene nada
};
//inline HUDManager& hud() {
//	return *HUDManager::GetInstance();
//}


