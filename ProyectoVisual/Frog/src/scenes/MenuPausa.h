#pragma once
#include "../ecs/Scene.h"
#include"../utils/Button.h"

#include <vector>

class Texture;
class InputManager;
class PausedState;
class Game;

enum direction { ARRIBA, ABAJO };

const int offsetX = 50;

class MenuPausa:public Scene
{
private:
	PausedState* pST;
	Game* game;
public:
	MenuPausa(Game* g, PausedState* s);
	~MenuPausa() {};
	void render() override;
	void update() override;
};

