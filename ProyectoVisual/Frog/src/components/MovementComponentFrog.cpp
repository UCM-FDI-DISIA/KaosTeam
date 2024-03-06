#include "MovementComponentFrog.h"
#include <iostream>
#include "../scenes/RoomScene.h"

void MovementComponentFrog::update() {
	//no te puedes mover más si ya te estás movimiendo
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
			isMoving = false;
			movementCompleted = true;
		}
	}

	else if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > actionCooldown) {
		if (im->getDown()) {
			destCasilla.setY(posCasilla.getY() + 1);
			actualDirection = DOWN;
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			jumping = true;
			isMoving = true;
			movementCompleted = false;
		}
		else if (im->getUp()) {
			destCasilla.setY(posCasilla.getY() -1);
			actualDirection = UP;
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			jumping = true;
			isMoving = true;
			movementCompleted = false;
		}
		else if (im->getRight()) {
			destCasilla.setX(posCasilla.getX() + 1);
			actualDirection = RIGHT;
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			jumping = true;
			isMoving = true;
			movementCompleted = false;
		}
		else if (im->getLeft()) {
			destCasilla.setX(posCasilla.getX() - 1);
			actualDirection = LEFT;
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			jumping = true;
			isMoving = true;
			movementCompleted = false;
		}
		
	}
}