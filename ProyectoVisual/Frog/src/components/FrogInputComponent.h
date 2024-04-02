#pragma once
#include "../ecs/Component.h"
#include "../managers/InputManager.h"
#include "MovementComponentFrog.h";
class AttackComponentFrog;
class FrogInputComponent : public Component
{
public:
	FrogInputComponent();
	void update() override;
	void setComponents(MovementComponentFrog* mvm, AttackComponentFrog* atck);

private:
	InputManager* input;
	int lastTimeMoved, actionCoolDown = 200;
	int LongJump = 2, shortJump = 1;
	int cyclesJumpPrepared = 0, cyclesToPrepareJump = 0;
	bool preparingJump;
	MovementComponentFrog* movementComponent;
	AttackComponentFrog* attackComponent;
};

