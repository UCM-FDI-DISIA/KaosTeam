#pragma once
#include "../ecs/Scene.h"
#include"../utils/Button.h"
#include <vector>
#include "../sdlutils/Texture.h"

enum direction{ARRIBA, ABAJO};

class MenuInicio : public Scene
{
private:
	Texture* menuBackground = nullptr;
	Texture* select = nullptr;
	SDL_Rect dest; //resize de la mosca
	int offsetX = 5;
	int offsetY = 50;
	std::vector <Button*> menuButton;
	int currentButton = 0;

public:
	MenuInicio();

	void render() override;
	void update() override;
	void changeButton(bool dir);
	void callButton();
};

