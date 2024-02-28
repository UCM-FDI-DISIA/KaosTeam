#include "MovementComponentFrog.h"
#include <iostream>

void MovementComponentFrog::update() {
	if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > actionCooldown) {
		if (im->getDown()) {
			destCasilla.setY(posCasilla.getY() + 1);
		}
		if (im->getUp()) {
			destCasilla.setY(posCasilla.getY() - 1);
		}
		if (im->getRight()) {
			destCasilla.setX(posCasilla.getX() + 1);
		}
		if (im->getLeft()) {
			destCasilla.setX(posCasilla.getX() - 1);
		}
		lastTimeMoved = DataManager::GetInstance()->getFrameTime(); //Esto más adelante habrá que cambiarlo para que use un mismo tiempo que el resto de componentes del juego
	}
	else if (destCasilla.getX() != posCasilla.getX() || destCasilla.getY() != posCasilla.getY()) {

	}

}