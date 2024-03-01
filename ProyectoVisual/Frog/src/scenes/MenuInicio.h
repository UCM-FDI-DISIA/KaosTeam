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
	int currentButton;

public:
	MenuInicio();

	void Render() override;
	void Update() override;
	void changeButton();
	void callButton();
};

