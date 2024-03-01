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
	std::vector <Button*> menuButton;
	int currentButton = 0;
	SDL_Rect dest; //resize de la mosca
	int offsetX = 5;

public:
	MenuInicio();

	void render() override;
	void update() override;
	void changeButton(bool dir);
	void callButton();
};

