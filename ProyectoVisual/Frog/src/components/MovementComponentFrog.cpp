#include "MovementComponentFrog.h"
#include <iostream>

void MovementComponentFrog::update() {
	if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > actionCooldown)
		if (im->getDown()) {
			posCasilla.setY(posCasilla.getY() + 1);
		}
		if (im->getUp()) {
			posCasilla.setY(posCasilla.getY() - 1);
		}
		if (im->getRight()) {
			posCasilla.setX(posCasilla.getX() + 1);
		}
		if (im->getLeft()) {
			posCasilla.setX(posCasilla.getX() - 1);
		}
		lastTimeMoved = DataManager::GetInstance()->getFrameTime(); //Esto más adelante habrá que cambiarlo para que use un mismo tiempo que el resto de componentes del juego
}