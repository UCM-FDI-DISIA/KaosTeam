#include "MovementComponentFly.h"

void MovementComponentFly::update()
{
	if ((SDL_GetTicks() - lastTimeMoved) > waitTime)
	{
		posCasilla = posCasilla + directions[status];

		status = (status + 1) % 4;
		lastTimeMoved = SDL_GetTicks();
	}
}
