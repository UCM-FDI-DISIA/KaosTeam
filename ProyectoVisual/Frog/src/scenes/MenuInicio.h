#pragma once
#include "../ecs/Scene.h"

#include "../components/FollowPlayerComponent.h"
class Texture;
class MenuInicio : public Scene
{
private:
	Texture* menuBackground = nullptr;

public:
	MenuInicio();
	MenuInicio(Texture* menuBG);

	void Render() override;
	void Update() override;
};

