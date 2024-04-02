#include "FrogInputComponent.h"
#include "../managers/DataManager.h"
#include "MovementComponentFrog.h"
#include "AttackComponentFrog.h"

FrogInputComponent::FrogInputComponent()
{
	input = InputManager::GetInstance();
}

void FrogInputComponent::update()
{
	if (input->getShift())
	{
		preparingJump = true;
		cyclesJumpPrepared++;
	}
	int JumpSize;
	if (cyclesJumpPrepared > cyclesToPrepareJump)
		JumpSize = LongJump;
	else
		JumpSize = shortJump;

	if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > actionCoolDown) {
		if (input->getDown()) {
			movementComponent->startMovement(DOWN, Vector2D(0, JumpSize), "DOWN");
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared= 0;

		}
		else if (input->getUp()) {
			movementComponent->startMovement(UP, Vector2D(0, -JumpSize), "UP");
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared = 0;

		}
		else if (input->getRight()) { 
			movementComponent->startMovement(RIGHT, Vector2D(JumpSize, 0), "RIGHT");
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared = 0;

		}
		else if (input->getLeft()) {
			movementComponent->startMovement(LEFT, Vector2D(-JumpSize, 0), "LEFT");
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared = 0;
		}
		else if (input->getSpace()) {
			attackComponent->attack();
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared = 0;
		}
		
	}

}

void FrogInputComponent::setComponents(MovementComponentFrog* mvm, AttackComponentFrog* atck)
{
	movementComponent = mvm;
	attackComponent = atck;
}
