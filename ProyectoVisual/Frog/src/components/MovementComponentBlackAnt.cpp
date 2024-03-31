#include "MovementComponentBlackAnt.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include "../scenes/RoomScene.h"

void MovementComponentBlackAnt::update() {

	if (!waitToAttack && !waitToMove && !isMoving && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime) {
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			
		switch (actualDirection)
		{
		case RIGHT: {
			if (isAtacking) {
				velocity = Vector2D(range, 0);
				//anim->playAnimation("RIGHT");
				isAtacking = false;
			}
			else {
				velocity = Vector2D(1, 0);
				//anim->playAnimation("RIGHT");
			}
			framesPerMove = 4 + velocity.magnitude() * 3;
		}
		break;
		case LEFT:
		{
			if (isAtacking) {
				velocity = Vector2D(-range, 0);
				//anim->playAnimation("LEFT");
				isAtacking = false;
			}
			else {
				velocity = Vector2D(-1, 0);
				//anim->playAnimation("LEFT");
			}
			framesPerMove = 4 + velocity.magnitude() * 3;
			
		}
		break;
		case UP:
		{
			if (isAtacking) {
				velocity = Vector2D(0, -range);
				//anim->playAnimation("LEFT");
				isAtacking = false;
			}
			else {
				velocity = Vector2D(0, -1);
				//anim->playAnimation("LEFT");
			}
			framesPerMove = 4 + velocity.magnitude() * 3;
		}
		break;
		case DOWN:
		{
			if (isAtacking) {
				velocity = Vector2D(0, range);
				//anim->playAnimation("LEFT");
				isAtacking = false;
			}
			else {
				velocity = Vector2D(0, 1);
				//anim->playAnimation("LEFT");
			}
			framesPerMove = 4 + velocity.magnitude() * 3;

		}
		break;
		default:
			break;
		}
		isMoving = true;
	}
	else if (isMoving && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > movementFrameRate) {
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
	
		int t = ent->getScene()->getMapReader()->getTileSize();
		framesMoved++;
		offsetInCasilla.setX(offsetInCasilla.getX() + t / framesPerMove * velocity.getX());

		if (offsetInCasilla.getX() * velocity.normalize().getX() >= t / 2 ||
			offsetInCasilla.getY() * velocity.normalize().getY() >= t / 2) //si se mueve mas de media casilla, est� en la casilla siguiente
		{
			changePos(velocity.normalize() + posCasilla);
			if (actualDirection == LEFT || actualDirection == RIGHT)
				offsetInCasilla.setX(offsetInCasilla.getX() * -1);
			else
				offsetInCasilla.setY(offsetInCasilla.getY() * -1);
		}
		if (framesMoved == framesPerMove) {
			//posCasilla = destCasilla;
			offsetInCasilla = { 0,0 };
			framesMoved = 0;
			isMoving = false;
			changeDirection();
			isPlayerNear();
			checkCollisionWall();
		}
	}
	else if (waitToAttack) {
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTimeAttack) {
			isAtacking = true;
			waitToAttack = false;
		}

	}
	else if (waitToMove) {
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > immobileTime) {
			waitToMove = false;
		}
	}
}
//metodo para cambiar de direccion y todo lo que conlleva eso
void MovementComponentBlackAnt::changeDirection() {
	int newDirection = rand_.nextInt(0, 4);
	//cambiar direccion
	switch (newDirection)
	{
		case 0: actualDirection = RIGHT;
			break;
		case 1: actualDirection = LEFT;
			break;
		case 2: actualDirection = UP;
			break;
		case 3: actualDirection = DOWN;
			break;
		default:
			break;
	}
}
void MovementComponentBlackAnt::isPlayerNear() {
	//cambiar direccion
	switch (actualDirection)
	{
	case RIGHT: {
		if (playerPosition.getX() - posCasilla.getX() <= 3) waitToAttack = true;
	}
		break;
	case LEFT: {
		if (posCasilla.getX() - playerPosition.getX()  <= 3) waitToAttack = true;
	}
		break;
	case UP: {
		if (posCasilla.getY() - playerPosition.getY() <= 3) waitToAttack = true;
	}
		break;
	case DOWN: {
		if (playerPosition.getY() - posCasilla.getY()  <= 3) waitToAttack = true;
	}
		break;
	default:
		break;
	}
	if (waitToAttack) {
		std::cout << "he detectado jugador";
	}
}
void MovementComponentBlackAnt::checkCollisionWall() {
	//comprobar si da con la pared y si es asi waitToMove = true
}
