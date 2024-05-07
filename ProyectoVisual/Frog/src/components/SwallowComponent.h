#pragma once

#include "../ecs/Component.h"
#include "ColliderComponent.h"
#include "InventoryComponent.h"
#include "AttackComponentFrog.h"
#include "../scenes/RoomScene.h"


class SwallowComponent : public Component {
private:
	ColliderComponent* coll;
	InventoryComponent* inv;
	TransformComponent* tr;
	bool isPicked;
	void checkCollisionsTongue(Entity* e, Collider c);
public:
	SwallowComponent();
	virtual ~SwallowComponent();
	void initComponent() override;
};

