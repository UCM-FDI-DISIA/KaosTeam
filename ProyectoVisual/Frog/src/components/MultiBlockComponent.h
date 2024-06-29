#pragma once
#include "../ecs/Component.h"
#include "../scenes/RoomScene.h"
#include "ColliderComponent.h"
#include "MovementComponentFrog.h"


class MultiBlockComponent :public Component
{
private:
	Vector2D position;
	ColliderComponent* coll = nullptr;
	RoomScene* scen = nullptr;
	void CheckCollisions(Entity* ent, Collider c);			// Checkea colisiones

public:
	MultiBlockComponent(Vector2D pos);
	//virtual ~MultiBlockComponent();
	void initComponent() override;
};

