#pragma once
#include "GameState.h"
#include "../ecs/Scene.h"
class InputManager;
class HUDManager;
class Game;

class PausedState:public GameState
{
public:
	PausedState(Game* game, HUDManager* hud, Scene& bg);
	~PausedState() {};
	void enter() override;
	void leave() override;
	void update() override;

	//	solo va a hacer update del menu d pausa
	//	scene->update()
	

private:
	HUDManager* hud; //Puntero que gestiona la pantalla de MenuInicio
	Scene& bgScene; //puede haber escenas d menu d opciones,etc.
	Scene& mPause;
	InputManager& imngr;
	Game*  game;
	//pauseMenuScene
};

