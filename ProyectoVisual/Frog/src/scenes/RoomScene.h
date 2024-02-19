#pragma once
#include "../ecs/Scene.h"

class RoomScene : public Scene
{
private:
	MapComponent* mapReader_;
public:
	RoomScene();

	void Render() override;
	void Update() override;
};