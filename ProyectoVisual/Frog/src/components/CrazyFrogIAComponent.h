#pragma once
#include "../ecs/Component.h"
#include "../managers/DataManager.h"
class MovementComponentFrog;
class AttackComponentFrog;
class CrazyFrogIAComponent : public Component
{
private: 
	int delayOfAction = 2200;
	int lastTimeMoved;
	Vector2D* playerPos = nullptr;
	AttackComponentFrog* attack;
	MovementComponentFrog* movement;

public:
	CrazyFrogIAComponent(MovementComponentFrog* mvm, AttackComponentFrog* atc) :
		movement(mvm), attack(atc), lastTimeMoved(DataManager::GetInstance()->getFrameTime()){};

	void update() override;
};

