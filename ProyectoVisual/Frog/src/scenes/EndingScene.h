#pragma once

#include "../game/Game.h"
#include "../ecs/Scene.h"

#include <string>
#include <vector>

class Texture;
class InputManager;
class GameState;

class EndingScene: public Scene
{
private:
	vector<Texture*>bgs;
	int currBg;
	SDL_Rect bgDest;
	GameState* gameState;
	Game* game;
	InputManager& imngr;
public:
    EndingScene(Game* g, GameState* nGS);
	virtual ~EndingScene();
	void render() override;
	void update() override;
};

