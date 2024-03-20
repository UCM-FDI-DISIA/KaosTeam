#pragma once
#include "GameState.h"
#include "../ecs/Scene.h"
class InputManager;
class HUDManager;
class Game;

class PausedState:public GameState
{
public:
	PausedState(Game* game);
	~PausedState() {};
	void enter() override;
	void leave() override;
	void update() override;

	//	solo va a hacer update del menu d pausa
	//	scene->update()
	

private:
	HUDManager& hudmngr; //Puntero que gestiona la pantalla de MenuInicio
	Scene* mPause;
	InputManager& imngr;
	Game*  game;
	//pauseMenuScene
};

