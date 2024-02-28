#pragma once
#include "../ecs/Scene.h"

class Texture;
class MenuInicio : public Scene
{
private:
	Texture* menuBackground = nullptr;

public:
	MenuInicio();

	void Render() override;
	void Update() override;
};

