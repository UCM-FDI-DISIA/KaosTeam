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
	if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > actionCoolDown) {

		if (input->getDown()) {
			movementComponent->startMovement(DOWN, Vector2D(0, 1), "DOWN");
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();

		}
		else if (input->getUp()) {
			movementComponent->startMovement(UP, Vector2D(0, -1), "UP");
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();

		}
		else if (input->getRight()) { 
			movementComponent->startMovement(RIGHT, Vector2D(1, 0), "RIGHT");
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();

		}
		else if (input->getLeft()) {
			movementComponent->startMovement(LEFT, Vector2D(-1, 0), "LEFT");
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		}
		else if (input->getSpace() && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > actionCoolDown) {
			attackComponent->attack();
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		}
		
	}

}

void FrogInputComponent::setComponents(MovementComponentFrog* mvm, AttackComponentFrog* atck)
{
	movementComponent = mvm;
	attackComponent = atck;
}
