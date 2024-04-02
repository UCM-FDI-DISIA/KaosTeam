#pragma once
#include "../ecs/Scene.h"

enum WhatMenu { INICIO, PAUSA, GAMEOVER }; //Define el tipo de menu a usar

class GameState {
public:

	GameState() {
	}

	virtual ~GameState() {
	}
	virtual void enter() = 0;
	virtual void leave() = 0;
	virtual void update() = 0;
	virtual Scene* getScene() const = 0;
};
