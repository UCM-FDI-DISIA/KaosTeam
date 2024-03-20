#include "MovementComponentFly.h"

void MovementComponentFly::update()
{
	if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime)
	{
		posCasilla = posCasilla + directions[status];

		status = (status + 1) % 4;

		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
	}

}
