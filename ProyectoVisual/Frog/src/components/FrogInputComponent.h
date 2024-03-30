#pragma once
#include "../ecs/Component.h"
#include "../managers/InputManager.h"
class MovementComponentFrog;
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
	MovementComponentFrog* movementComponent;
	AttackComponentFrog* attackComponent;
};

