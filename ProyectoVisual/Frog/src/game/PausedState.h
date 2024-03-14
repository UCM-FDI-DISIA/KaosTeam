#pragma once
#include "GameState.h"
#include "../ecs/Scene.h"
class InputManager;

class PausedState:public GameState, public Scene
{
	PausedState();
	~PausedState() {};
	void enter() override;
	void leave() override;
	void update() override;
	void render() override;
	InputManager& imngr;
};

