#include "MovementComponentRedAnt.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include "../scenes/RoomScene.h"
void MovementComponentRedAnt::canMove(Vector2D vel, Direction dir) {
	Vector2D aux = posCasilla + vel;
	switch (dir) {
	case MovementComponentRedAnt::RIGHT:
	{
		if (checkIfTileWalkable(aux)) {
			velocity = Vector2D(1, 0);
		}
	}
	break;
	case MovementComponentRedAnt::LEFT:
	{
		if (aux.getX() >= 0) {
			velocity = Vector2D(-1, 0);
		}
	}
	break;
	case MovementComponentRedAnt::UP:
	{
		if (aux.getY() >= 0) {
			velocity = Vector2D(0, -1);
		}
	}
	break;
	case MovementComponentRedAnt::DOWN:
	{
		if (checkIfTileWalkable(aux)) {
			velocity = Vector2D(0, 1);
		}
	}
	break;
	}
}
void MovementComponentRedAnt::update() {

	if (!isMoving && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime) {
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		playerPosition = targetMovementComp->getPosition();
		switch (actualDirection)
		{
		case RIGHT: {
			//velocity = Vector2D(1, 0);
			canMove(Vector2D(1, 0), RIGHT);
			if (escape) {

				//velocity = Vector2D(range, 0);
				//anim->playAnimation("RIGHT");
				framesPerMove = 2 + velocity.magnitude() * 3;
			}
			else {
				//anim->playAnimation("RIGHT");
				framesPerMove = 4 + velocity.magnitude() * 3;
			}
		}
				  break;
		case LEFT:
		{
			//velocity = Vector2D(-1, 0);
			canMove(Vector2D(-1, 0), LEFT);
			if (escape) {
				//velocity = Vector2D(-range, 0);
				//anim->playAnimation("LEFT");
				framesPerMove = 2 + velocity.magnitude() * 3;
			}
			else {
				//anim->playAnimation("LEFT");
				framesPerMove = 4 + velocity.magnitude() * 3;
			}
		}
		break;
		case UP:
		{
			//velocity = Vector2D(0, -1);
			canMove(Vector2D(0, -1), UP);
			if (escape) {
				//velocity = Vector2D(0, -range);
				//anim->playAnimation("LEFT");
				framesPerMove = 2 + velocity.magnitude() * 3;
			}
			else {
				//anim->playAnimation("LEFT");
				framesPerMove = 4 + velocity.magnitude() * 3;
			}
		}
		break;
		case DOWN:
		{
			//velocity = Vector2D(0, 1);
			canMove(Vector2D(0, 1), DOWN);
			if (escape) {
				//velocity = Vector2D(0, range);
				//anim->playAnimation("LEFT");
				framesPerMove = 2 + velocity.magnitude() * 3;
			}
			else {
				//anim->playAnimation("LEFT");
				framesPerMove = 4 + velocity.magnitude() * 3;
			}
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
		if (actualDirection == RIGHT || actualDirection == LEFT) {
			offsetInCasilla.setX(offsetInCasilla.getX() + t / framesPerMove * velocity.getX());
		}
		else {
			offsetInCasilla.setY(offsetInCasilla.getY() + t / framesPerMove * velocity.getY());
		}

		if (offsetInCasilla.getX() * velocity.normalize().getX() >= t / 2 ||
			offsetInCasilla.getY() * velocity.normalize().getY() >= t / 2)
		{
			changePos(velocity.normalize() + posCasilla);
			if (actualDirection == LEFT || actualDirection == RIGHT)
				offsetInCasilla.setX(offsetInCasilla.getX() * -1);
			else if (actualDirection == UP || actualDirection == DOWN)
				offsetInCasilla.setY(offsetInCasilla.getY() * -1);
		}
		if (framesMoved == framesPerMove) {
			offsetInCasilla = { 0,0 };
			framesMoved = 0;
			isMoving = false;
			if (escape) escape = false;
			isPlayerNear();
			if (!escape) {
				changeDirection();
			}
		}
	}
}
//metodo para cambiar de direccion y todo lo que conlleva eso
void MovementComponentRedAnt::changeDirection() {
	int newDirection = rand_.nextInt(0, 4);
	//cambiar direccion
	switch (newDirection)
	{
	case 0: {
		Vector2D aux = posCasilla + Vector2D(1, 0);
		if (checkIfTileWalkable(aux)) {
			actualDirection = RIGHT;
		}
		else
			changeDirection();
	}
		  break;
	case 1: {
		Vector2D aux = posCasilla + Vector2D(-1, 0);
		/*if (checkIfTileWalkable(aux)) {
			actualDirection = LEFT;
		}*/
		if (aux.getX() >= 0) {
			actualDirection = LEFT;
		}
		else
			changeDirection();
	}
		  break;
	case 2: {
		Vector2D aux = posCasilla + Vector2D(0, -1);
		/*if (checkIfTileWalkable(aux)) {
			actualDirection = UP;
		}*/
		if (aux.getY() >= 0) {
			actualDirection = UP;
		}
		else
			changeDirection();

	}
		  break;
	case 3: {
		Vector2D aux = posCasilla + Vector2D(0, 1);
		if (checkIfTileWalkable(aux)) {
			actualDirection = DOWN;
		}
		else
			changeDirection();
	}
		  break;
	default:
		break;
	}
}
void MovementComponentRedAnt::isPlayerNear() {
	if (playerPosition.getY() == posCasilla.getY()) {
		if (playerPosition.getX() - posCasilla.getX() <= range && playerPosition.getX() - posCasilla.getX() > 0) {
			if (actualDirection == RIGHT) actualDirection = LEFT;
			escape = true;
		}
		else if (!escape && posCasilla.getX() - playerPosition.getX() <= range && posCasilla.getX() - playerPosition.getX() > 0) {
			if (actualDirection == LEFT) actualDirection = RIGHT;
			escape = true;
		}
	}
	else if (!escape && playerPosition.getX() == posCasilla.getX()) {
		if (playerPosition.getY() - posCasilla.getY() <= range && playerPosition.getY() - posCasilla.getY() > 0) {
			if (actualDirection == DOWN) actualDirection = UP;
			escape = true;
		}
		else if (!escape && posCasilla.getY() - playerPosition.getY() <= range && posCasilla.getY() - playerPosition.getY() > 0) {
			if (actualDirection == UP) actualDirection = DOWN;
			escape = true;
		}
	}
}
