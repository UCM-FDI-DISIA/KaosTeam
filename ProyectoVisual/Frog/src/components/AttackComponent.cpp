#include "AttackComponent.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"



void AttackComponent::update()
{
	if ((DataManager::GetInstance()->getFrameTime() - lastTimeChanged) > attackFrameTime)
	{
		lastTimeChanged = DataManager::GetInstance()->getFrameTime();
		if (state == 1)
		{
			distanceMoved++;
			if (distanceMoved == attackDistance)
				state++;

		}
		else if (state == 2)
		{
			distanceMoved--;
			if (distanceMoved == 0)
				state = 0;
		}
		
	}
	if (state == 0 && inputM->getSpace())
	{
		state = 1;
	}
	
}
