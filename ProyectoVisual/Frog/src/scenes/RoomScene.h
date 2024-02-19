#pragma once
#include "../ecs/Scene.h"
#include "../ecs/Entity.cpp"

class RoomScene : public Scene
{
private:
	//Camara
	std::vector<Entity*> entityList;
	MapComponent* mapReader;
public:
	RoomScene();

	void Render() override;
	void Update() override;
};