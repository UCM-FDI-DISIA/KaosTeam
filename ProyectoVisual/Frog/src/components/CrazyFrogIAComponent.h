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
	Vector2D* playerPos;
	AttackComponentFrog* attack;
	MovementComponentFrog* movement;

public:
	CrazyFrogIAComponent(MovementComponentFrog* mvm, AttackComponentFrog* atc) :playerPos(nullptr),
		movement(mvm), attack(atc), lastTimeMoved(DataManager::GetInstance()->getFrameTime()){};

	void update() override;
};

