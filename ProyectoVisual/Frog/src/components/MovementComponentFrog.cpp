#include "MovementComponentFrog.h"
#include <iostream>
#include "../scenes/RoomScene.h"

void MovementComponentFrog::update() {
	//no te puedes mover m�s si ya te est�s movimiendo
	if (jumping && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > movementFrameRate)
	{
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		int t = ent->getScene()->getMapReader()->getTileSize();
			
		framesMoved++;
		
		if (actualDirection == LEFT || actualDirection == RIGHT)
		{
			offsetInCasilla.setX(t / framesPerJump * framesMoved * (destCasilla.getX() - posCasilla.getX()));
			offsetInCasilla.setY(-t/2 * sin(3.14/framesPerJump * framesMoved)); //para calcular la altura del salto
		}
		else
		{
			offsetInCasilla.setY(t / framesPerJump * framesMoved * (destCasilla.getY() - posCasilla.getY()));
		}

		if (framesMoved == framesPerJump) //para acabar el movimiento
		{
			posCasilla = destCasilla;
			offsetInCasilla = { 0,0 };
			framesMoved = 0;
			jumping = false;
		}
	}

	else if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > actionCooldown) {
		if (im->getDown() && posCasilla.getY()< boundY) { //revisar limite
			destCasilla.setY(posCasilla.getY() + 1);
			actualDirection = DOWN;
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			jumping = true;
		}
		else if (im->getUp() && posCasilla.getY() > 0) {
			destCasilla.setY(posCasilla.getY() -1);
			actualDirection = UP;
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			jumping = true;
		}
		else if (im->getRight() && posCasilla.getX() < boundX) { //revisar limite
			destCasilla.setX(posCasilla.getX() + 1);
			actualDirection = RIGHT;
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			jumping = true;
		}
		else if (im->getLeft() && posCasilla.getX() > 0) {
			destCasilla.setX(posCasilla.getX() - 1);
			actualDirection = LEFT;
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			jumping = true;
		}
		
	}
}