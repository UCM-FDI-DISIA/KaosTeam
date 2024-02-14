#pragma once
#include "../ecs/Scene.h"

class MenuInicio : public Scene
{
public:
	MenuInicio();

	void Render() override;
	void Update() override;
};

