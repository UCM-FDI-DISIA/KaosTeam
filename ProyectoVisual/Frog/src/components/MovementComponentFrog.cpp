#include "MovementComponentFrog.h"
#include <iostream>
#include "../scenes/RoomScene.h"

void MovementComponentFrog::startMovement(Directions d, Vector2D v)
{
	if (checkIfTileWalkable(posCasilla + v))
	{
		actualDirection = d;
		velocity = v;
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		jumping = true;
	}
	
}

void MovementComponentFrog::update() {
	//no te puedes mover m�s si ya te est�s movimiendo
	if (jumping && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > movementFrameRate)
	{
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		int t = ent->getScene()->getMapReader()->getTileSize();
			
		framesMoved++;
		
		if (actualDirection == LEFT || actualDirection == RIGHT)
		{
			offsetInCasilla.setX(t / framesPerJump * framesMoved * velocity.getX());
			offsetInCasilla.setY(-t/2 * sin(3.14/framesPerJump * framesMoved)); //para calcular la altura del salto
		}
		else
		{
			offsetInCasilla.setY(t / framesPerJump * framesMoved * velocity.getY() );
		}


		if (framesMoved == framesPerJump) //para acabar el movimiento
		{
			changePos(velocity + posCasilla);
			offsetInCasilla = { 0,0 };
			framesMoved = 0;
			jumping = false;
		}
	}

	else if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > actionCooldown) {
		if (im->getDown() && posCasilla.getY()< boundY) { //revisar limite
			startMovement(DOWN,	Vector2D(0, 1));
		
		}
		else if (im->getUp() && posCasilla.getY() > 0) {
			startMovement(UP, Vector2D(0, -1));

		}
		else if (im->getRight() && posCasilla.getX() < boundX) { //revisar limite
			startMovement(RIGHT, Vector2D(1, 0));

		}
		else if (im->getLeft() && posCasilla.getX() > 0) {
			startMovement(LEFT, Vector2D(-1, 0));

		}
		
	}
}