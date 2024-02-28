#include "MovementComponentRana.h"
#include <iostream>
void MovementComponentRana::update() {

	if ((SDL_GetTicks() - lastTimeMoved) > actionCooldown)
	{
		if (im->getDown()) {
			posCasilla.setY(posCasilla.getY() - 1);
		}
	}
}