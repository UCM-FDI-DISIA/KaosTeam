#pragma once
#include "../ecs/Scene.h"
#include"../utils/Button.h"
#include <vector>

class Texture;
class MenuInicio : public Scene
{
private:
	Texture* menuBackground = nullptr;
	std::vector <Button*> menuButton;
	int currentButton = 0;

public:
	MenuInicio();

	void render() override;
	void update() override;
	void changeButton();
	void callButton();
};

