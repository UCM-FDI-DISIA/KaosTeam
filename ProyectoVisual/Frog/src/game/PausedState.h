#pragma once
#include "GameState.h"
#include "../ecs/Scene.h"
class InputManager;

class PausedState:public GameState, public Scene
{
public:
	PausedState();
	~PausedState() {};
	void enter() override;
	void leave() override;
	void update() override/* {

		solo va a hacer update del menu d pausa
		scene->update()
	}*/;
	void render() override /* {

		va a renderizar las tres escenas (bg y hud del running y el menu d pausa
	}*/;
	

private:
	HUDManager* hud; //Puntero que gestiona la pantalla de MenuInicio
	Scene& bgScene; //puede haber escenas d menu d opciones,etc.
	Scene& mPause;
	InputManager& imngr;
	//pauseMenuScene
};

