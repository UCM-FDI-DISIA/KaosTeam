#include "MovementComponentFly.h"
#include "TransformComponent.h"

void MovementComponentFly::update()
{
	if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime)
	{
		tr->setCasilla(tr->getCasilla() + directions[status]);

		status = (status + 1) % 4;

		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
	}

}
