#pragma once
#include "GameState.h"
#include "../ecs/Scene.h"
class InputManager;
class HUDManager;

class PausedState:public GameState
{
public:
	PausedState(HUDManager* hud_, Scene& bg_, Scene& pause_);
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
	//pauseMenuScene
};

