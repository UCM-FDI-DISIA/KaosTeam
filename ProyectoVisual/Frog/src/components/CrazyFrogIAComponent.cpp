#include "CrazyFrogIAComponent.h"
#include "AttackComponentFrog.h"
#include "MovementComponentFrog.h"
#include "../scenes/RoomScene.h"
#include "../ecs/Entity.h"

void CrazyFrogIAComponent::update()
{
	if (DataManager::GetInstance()->getFrameTime() - lastTimeMoved > delayOfAction)
	{
		//solo se hace una vez. Podemos hacerlo en el init. Pero por ahora lo tengo aqui
		if (playerPos == nullptr)
			playerPos = static_cast<MovementComponent*>(ent->getScene()->getPlayer()->getComponent(MOVEMENT_COMPONENT))->getPosPointer();

		cout << "actualizando rana";

		Vector2D aux = *playerPos - movement->getPosition();
		
		//calculamos en que dirección deberiamos movernos
		Vector2D speed; Directions direction; string animation;
		if ((unsigned int)aux.getX() > (unsigned int)aux.getY())
		{
			if (aux.getX() > 0)
			{
				speed = { 1, 0 };
				direction = RIGHT;
				animation = "RIGHT";
			}
				
			else
			{
				speed = { -1, 0 };
				direction = LEFT;
				animation = "LEFT";
			}
		}
		else
		{
			if (aux.getY() > 0)
			{
				speed = { 0, 1 };
				direction = DOWN;
				animation = "DOWN";
			}
			else
			{
				speed = {0, -1 };
				direction = UP;
				animation = "UP";
			}
		}

		//si debemos atacar o acercarnos
		if (aux.magnitude() < 3 && (aux.getX() == 0 || aux.getY() == 0))
		{
			movement->changeDirection(direction, animation);
			attack->attack();
		}
		else
		{
			movement->startMovement(direction, speed, animation);
		}
			

		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
	}
}
