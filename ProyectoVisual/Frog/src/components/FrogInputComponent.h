#pragma once
#include "../ecs/Component.h"
#include "../managers/InputManager.h"
#include "MovementComponentFrog.h"
#include "InventoryComponent.h"
class AttackComponentFrog;
class FrogInputComponent : public Component
{
public:
	FrogInputComponent();
	~FrogInputComponent();
	void update() override;
	void setComponents(MovementComponentFrog* mvm, AttackComponentFrog* atck, InventoryComponent* invComp);

private:
	InputManager* input;
	int lastTimeMoved, actionCoolDown = 200;
	int longJump = 2, shortJump = 1;
	int longTongue = 5, shortTongue = 2;
	int cyclesJumpPrepared = 0, cyclesToPrepareJump = 20;
	bool preparingJump;
	MovementComponentFrog* movementComponent;
	AttackComponentFrog* attackComponent;
	InventoryComponent* inventoryComponent;
};

