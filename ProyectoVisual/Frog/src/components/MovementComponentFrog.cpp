#include "MovementComponentFrog.h"
#include <iostream>
void MovementComponentFrog::update() {

		if (im->getDown()) {
			posCasilla.setY(posCasilla.getY() + 1);
		}
		lastTimeMoved = SDL_GetTicks(); //Esto más adelante habrá que cambiarlo para que use un mismo tiempo que el resto de componentes del juego

}