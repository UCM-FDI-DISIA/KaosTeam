#pragma once

#include "../game/Game.h"
#include "../ecs/Scene.h"

#include <string>
#include <vector>

class Texture;
class InputManager;
class GameState;
const int NUM_TEXT = 4;
const int TRANSITION_TIME = 3000;
class EndingScene: public Scene
{
private:
	vector<Texture*>bgs;
	int currBg;
	SDL_Rect bgDest;
	GameState* gameState;
	Game* game;
	InputManager& imngr;
	float initTime;
public:
    EndingScene(Game* g, GameState* nGS);
	void changeInitTime();
	virtual ~EndingScene();
	void render() override;
	void update() override;
};

