#include "FrogInputComponent.h"
#include "../managers/DataManager.h"
#include "MovementComponentFrog.h"
#include "AttackComponentFrog.h"

FrogInputComponent::FrogInputComponent() : movementComponent(nullptr), attackComponent(nullptr), inventoryComponent(nullptr)
{
	input = InputManager::GetInstance();
}
FrogInputComponent::~FrogInputComponent()
{
	movementComponent = nullptr;
	attackComponent = nullptr;
	inventoryComponent = nullptr;
}
void FrogInputComponent::update()
{
	////mover shortJump y LngJump al movemente despues del hito
	//int JumpSize = shortJump;
	//if (input->getAction2())
	//{
	//	preparingJump = true;
	//	cyclesJumpPrepared++;
	//	if (cyclesJumpPrepared > cyclesToPrepareJump)
	//		JumpSize = longJump;
	//}
	//
	//else
	//	cyclesJumpPrepared = 0;
		
	int JumpSize = shortJump;
	if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > actionCoolDown) {
		if (input->getDown()) {
			if (inventoryComponent->mejoras.saltamontes && input->getShift().pressed) {
				JumpSize = longJump;
			}
			else JumpSize = shortJump;
			movementComponent->startMovement(DOWN, Vector2D(0, JumpSize));
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared= 0;

		}
		else if (input->getUp()) {
			if (inventoryComponent->mejoras.saltamontes && input->getShift().pressed) {
				JumpSize = longJump;
			}
			else JumpSize = shortJump;
			movementComponent->startMovement(UP, Vector2D(0, -JumpSize));
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared = 0;

		}
		else if (input->getRight()) { 
			if (inventoryComponent->mejoras.saltamontes && input->getShift().pressed) {
				JumpSize = longJump;
			}
			else JumpSize = shortJump;
			movementComponent->startMovement(RIGHT, Vector2D(JumpSize, 0));
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared = 0;

		}
		else if (input->getLeft()) {
			if (inventoryComponent->mejoras.saltamontes && input->getShift().pressed) {
				JumpSize = longJump;
			}
			else JumpSize = shortJump;
			movementComponent->startMovement(LEFT, Vector2D(-JumpSize, 0));
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared = 0;
		}
		else if (input->getSpace()) {
			if (inventoryComponent->mejoras.ciempies && input->getShift().pressed) {
				attackComponent->setDistance(longTongue);
			}
			else attackComponent->setDistance(shortTongue);
			attackComponent->attack();
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared = 0;
		}
		else if (input->getM()) { //ATAQUE CON HOOK DECIDIR CÓMO LO VAMOS A HACER
			if (inventoryComponent->mejoras.ciempies && input->getShift().pressed) {
				attackComponent->setDistance(longTongue);
			}
			else attackComponent->setDistance(shortTongue+2);
			attackComponent->attack(true);
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			preparingJump = false;
			cyclesJumpPrepared = 0;
		}
		else if (input->getAction5()) { //Pongo aquí un caso para lanzar bomba (Aunque habría que comprobar antes que la rana tenga la capacidad de guardar bombas)
			if (inventoryComponent->habilidades.sacoBombas) {
				//attackComponent->
				std::cout << "HAS LANZADO BOMBAS CON EL SACO" << std::endl;
			}
		}
		//else if (input->getAction2()) { 
		//}
	}

}

void FrogInputComponent::setComponents(MovementComponentFrog* mvm, AttackComponentFrog* atck,InventoryComponent* invComp )
{
	movementComponent = mvm;
	attackComponent = atck;
	inventoryComponent = invComp;
}
