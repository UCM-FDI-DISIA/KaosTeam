#pragma once
#include "GameState.h"
#include "../ecs/Scene.h"
class InputManager;

class PausedState:public GameState
{
private:
	InputManager& imngr;

public:
	PausedState();
	~PausedState() {};
	void enter() override;
	void leave() override;
	void update() override;


};

