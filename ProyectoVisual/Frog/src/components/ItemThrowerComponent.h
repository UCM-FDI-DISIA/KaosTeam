#pragma once
#include "../ecs/Component.h"
#include "InventoryComponent.h"
#include "../scenes/RoomScene.h"
class ItemThrowerComponent : public Component {
private:
	InventoryComponent* inv;
	TransformComponent* playerTr;

public:
	ItemThrowerComponent();
	virtual ~ItemThrowerComponent();
	void initComponent() override;
	void throwItem(Items object, MovementComponentFrog* mvFrog);
	void throwStart();
};
