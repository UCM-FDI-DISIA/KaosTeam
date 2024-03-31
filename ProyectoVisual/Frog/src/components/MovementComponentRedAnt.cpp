#include "MovementComponentRedAnt.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include "../scenes/RoomScene.h"

void MovementComponentRedAnt::update() {

	if (!isMoving && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime) {
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();

		switch (actualDirection)
		{
		case RIGHT: {
			if (escape) {
				velocity = Vector2D(range, 0);
				//anim->playAnimation("RIGHT");
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
			if (escape) {
				velocity = Vector2D(-range, 0);
				//anim->playAnimation("LEFT");
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
			if (escape) {
				velocity = Vector2D(0, -range);
				//anim->playAnimation("LEFT");
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
			if (escape) {
				velocity = Vector2D(0, range);
				//anim->playAnimation("LEFT");
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
			isPlayerNear();
			if (!escape) {
				changeDirection();
			}
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
void MovementComponentRedAnt::isPlayerNear() {
	//cambiar direccion
	switch (actualDirection)
	{
	case RIGHT: {
		if (playerPosition.getX() - posCasilla.getX() <= 3) {
			escape = true;
			actualDirection = LEFT;
		}
		else {
			escape = false;
		}
	}
	break;
	case LEFT: {
		if (posCasilla.getX() - playerPosition.getX() <= 3) {
			escape = true;
			actualDirection = RIGHT;
		}
		else {
			escape = false;
		}
	}
	break;
	case UP: {
		if (posCasilla.getY() - playerPosition.getY() <= 3) {
			escape = true;
			actualDirection = DOWN;
		}
		else {
			escape = false;
		}
	}
	break;
	case DOWN: {
		if (playerPosition.getY() - posCasilla.getY() <= 3) {
			escape = true;
			actualDirection = UP;
		}
		else {
			escape = false;
		}
	}
	break;
	default:
		break;
	}
	if (escape) {
		std::cout << "he detectado jugador";
	}
}
