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
	~PausedState();
	void enter() override;
	void leave() override;
	void update() override;
	Scene* getScene() const override { return mPause; }
	//	solo va a hacer update del menu d pausa
	//	scene->update()
	

private:
	Scene* menu;
	InputManager& imngr;
	Game*  game;
	Scene& currScene; //puede haber escenas d menu d opciones,etc.
};

