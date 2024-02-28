#pragma once
#include "../ecs/Scene.h"

#include "../components/FollowPlayerComponent.h"

class MenuInicio : public Scene
{
private:


public:
	MenuInicio();

	void Render() override;
	void Update() override;
};

