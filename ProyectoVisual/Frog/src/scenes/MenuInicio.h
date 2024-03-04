#pragma once
#include "../ecs/Scene.h"
#include"../utils/Button.h"
#include "../game/Game.h"
#include "../sdlutils/Texture.h"
#include"../managers/InputManager.h"

#include <vector>

enum direction{ARRIBA, ABAJO};

const int offsetX = 50;

class MenuInicio : public Scene
{
private:
	Texture* menuBackground = nullptr;
	Texture* select = nullptr;
	SDL_Rect dest; //resize de la mosca
	std::vector <Button*> menuButton;
	int currentButton = 0;
	InputManager* im;
	Game* game;
public:
	MenuInicio() {};

	MenuInicio(Game* g);

	void render() override;
	void update() override;
	void changeButton(bool dir);
	void callButton();
};

