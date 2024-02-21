#pragma once
#include "../ecs/Scene.h"
#include "../components/MovementComponent.h"
#include "../components/RenderComponent.h"

class MenuInicio : public Scene
{
public:
	MenuInicio();

	void Render() override;
	void Update() override;
};

