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
	//mover shortJump y LngJump al movemente despues del hito
	int JumpSize = shortJump;
	if (input->getAction2())
	{
		preparingJump = true;
		cyclesJumpPrepared++;
		if (cyclesJumpPrepared > cyclesToPrepareJump)
			JumpSize = LongJump;
	}
	
	else
		cyclesJumpPrepared = 0;
		

	if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > actionCoolDown) {
		if (input->getDown()) {
			if (inventoryComponent->getJumpUpgrade() && input->getShift().pressed) {
				JumpSize = longJump;
			}
			else JumpSize = shortJump;
			movementComponent->startMovement(DOWN, Vector2D(0, JumpSize));
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared= 0;

		}
		else if (input->getUp()) {
			if (inventoryComponent->getJumpUpgrade() && input->getShift().pressed) {
				JumpSize = longJump;
			}
			else JumpSize = shortJump;
			movementComponent->startMovement(UP, Vector2D(0, -JumpSize));
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared = 0;

		}
		else if (input->getRight()) { 
			if (inventoryComponent->getJumpUpgrade() && input->getShift().pressed) {
				JumpSize = longJump;
			}
			else JumpSize = shortJump;
			movementComponent->startMovement(RIGHT, Vector2D(JumpSize, 0));
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared = 0;

		}
		else if (input->getLeft()) {
			if (inventoryComponent->getJumpUpgrade() && input->getShift().pressed) {
				JumpSize = longJump;
			}
			else JumpSize = shortJump;
			movementComponent->startMovement(LEFT, Vector2D(-JumpSize, 0));
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
		else if (input->getM()) { //ATAQUE CON HOOK DECIDIR C�MO LO VAMOS A HACER
			if (inventoryComponent->getAttackUpgrade() && input->getShift().pressed) {
				attackComponent->setDistance(longTongue);
			}
			else attackComponent->setDistance(shortTongue+1);
			attackComponent->attack(true);
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared = 0;
		}
		//else if (input->getAction2()) { //Pongo aqu� un caso para lanzar bomba (Aunque habr�a que comprobar antes que la rana tenga la capacidad de guardar bombas)
		//}
	}

}

void FrogInputComponent::setComponents(MovementComponentFrog* mvm, AttackComponentFrog* atck)
{
	movementComponent = mvm;
	attackComponent = atck;
}
