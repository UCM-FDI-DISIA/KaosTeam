#pragma once
#include "../ecs/Scene.h"
//#include "../ecs/Entity.h"
#include"../components/MovementComponent.h"
#include "../components/RenderComponent.h"

class RoomScene : public Scene
{
private:
	//Camara
public:
	RoomScene();

	void Render() override;
	void Update() override;
};