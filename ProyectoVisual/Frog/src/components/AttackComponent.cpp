#include "AttackComponent.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"



void AttackComponent::update()
{
	if ((SDL_GetTicks() - lastTimeChanged) > attackFrameTime)
	{
		lastTimeChanged = SDL_GetTicks();
		if (state == 1)
		{
			distanceMoved++;
			if (distanceMoved == attackDistance)
				state++;

		}
		else if (state == 2)
		{
			distanceMoved--;
			if (distanceMoved == 1)
				state = 1;
		}
		else
		{
			//pregunar si hay q atacar
		}
	}
	
}
