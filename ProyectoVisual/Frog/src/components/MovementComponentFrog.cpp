#include "MovementComponentFrog.h"
#include "../scenes/RoomScene.h"


void MovementComponentFrog::startMovement(Directions d, Vector2D v, std::string animation)
{
	if (!jumping && checkIfTileWalkable(posCasilla + v))
	{
		actualDirection = d;
		velocity = v;
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		jumping = true;
		framesPerJump = 4 + v.magnitude()*3; //2 frames de despegue, 3 en cada casilla, 2 de aterrizaje
	}
	anim->playAnimation(animation);
}

void MovementComponentFrog::update() {
	if (jumping && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > movementFrameRate)
	{
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		int t = ent->getScene()->getMapReader()->getTileSize();
			
		framesMoved++;
		
		if (actualDirection == LEFT || actualDirection == RIGHT)
		{
			offsetInCasilla.setX(offsetInCasilla.getX() + t / framesPerJump * velocity.getX());
			offsetInCasilla.setY(-t/2 * sin(3.14/framesPerJump * framesMoved)); //para calcular la altura del salto
		}
		else
		{
			offsetInCasilla.setY(offsetInCasilla.getY() + t / framesPerJump * velocity.getY());
		}


		if (offsetInCasilla.getX()*velocity.normalize().getX() >= t / 2 ||
			offsetInCasilla.getY() * velocity.normalize().getY() >= t / 2) //si se mueve mas de media casilla, está en la casilla siguiente
		{
			changePos(velocity.normalize() + posCasilla);
			if (actualDirection == LEFT || actualDirection == RIGHT)
				offsetInCasilla.setX(offsetInCasilla.getX() * -1);
			else
				offsetInCasilla.setY(offsetInCasilla.getY() * -1);
		}

		if (framesMoved == framesPerJump) //para acabar el movimiento
		{
			//changePos(velocity.normalize() + posCasilla);
			offsetInCasilla = {0,0};
			framesMoved = 0;
			jumping = false;
		}
	}
}