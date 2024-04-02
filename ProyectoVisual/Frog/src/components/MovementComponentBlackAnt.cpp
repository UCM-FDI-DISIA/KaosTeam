#include "MovementComponentBlackAnt.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include "../scenes/RoomScene.h"

void MovementComponentBlackAnt::update() {

	if (!waitToAttack && !waitToMove && !isMoving && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime) {
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		playerPosition = targetMovementComp->getPosition();
		switch (actualDirection)
		{
		case RIGHT: {
			if (isAtacking) {
				velocity = Vector2D(diff, 0);
				//anim->playAnimation("RIGHT");
				framesPerMove = 2 + velocity.magnitude() * 3;
			}
			else {
				velocity = Vector2D(1, 0);
				//anim->playAnimation("RIGHT");
				framesPerMove = 4 + velocity.magnitude() * 3;
			}
		}
		break;
		case LEFT:
		{
			if (isAtacking) {
				velocity = Vector2D(diff, 0);
				//anim->playAnimation("LEFT");
				framesPerMove = 2 + velocity.magnitude() * 3;
			}
			else {
				velocity = Vector2D(-1, 0);
				//anim->playAnimation("LEFT");
				framesPerMove = 4 + velocity.magnitude() * 3;
			}
		}
		break;
		case UP:
		{
			if (isAtacking) {
				velocity = Vector2D(0, diff);
				//anim->playAnimation("LEFT");
				framesPerMove = 2 + velocity.magnitude() * 3;
			}
			else {
				velocity = Vector2D(0, -1);
				//anim->playAnimation("LEFT");
				framesPerMove = 4 + velocity.magnitude() * 3;
			}
		}
		break;
		case DOWN:
		{
			if (isAtacking) {
				velocity = Vector2D(0, diff);
				//anim->playAnimation("LEFT");
				framesPerMove = 4 + velocity.magnitude() * 3;;
			}
			else {
				velocity = Vector2D(0, 1);
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
	else if (isMoving && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > movementFrameRate)
	{
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
			if (isAtacking) {
				diff = 0;
				isAtacking = false;
				checkCollisionWall();
			}
			bool attack = isPlayerNear();
			if (!attack)
				changeDirection();
		}
	}
	else if (waitToAttack) {
		Uint32 currentTime = DataManager::GetInstance()->getFrameTime();
		if ((currentTime - lastTimeMoved) > waitTimeAttack) {
			isAtacking = true;
			waitToAttack = false;
			lastTimeMoved = currentTime;
		}
	}
	else if (waitToMove) {
		Uint32 currentTime = DataManager::GetInstance()->getFrameTime();
		if ((currentTime - lastTimeMoved) > immobileTime) {
			waitToMove = false;
			lastTimeMoved = currentTime;
		}
	}
}
//metodo para cambiar de direccion y todo lo que conlleva eso
void MovementComponentBlackAnt::changeDirection() {
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
bool MovementComponentBlackAnt::isPlayerNear() {
	if (playerPosition.getY() == posCasilla.getY() && playerPosition.getX() - posCasilla.getX() <= range) {
		waitToAttack = true;
		diff = playerPosition.getX() - posCasilla.getX();
		if (diff > 0)
			actualDirection = RIGHT;
		else if (diff < 0)
			actualDirection = LEFT;
	}
	else if (!waitToAttack && playerPosition.getX() == posCasilla.getX() && playerPosition.getY() - posCasilla.getY() <= range) {
		waitToAttack = true;
		isAtacking = true;
		diff = playerPosition.getY() - posCasilla.getY();
		if (diff > 0)
			actualDirection = DOWN;

		else if (diff < 0)
			actualDirection = UP;
	}
	return waitToAttack;
}
void MovementComponentBlackAnt::checkCollisionWall() {
	//comprobar si da con la pared y si es asi waitToMove = true
	if (actualDirection == RIGHT && !checkIfTileWalkable(posCasilla + Vector2D(1, 0)))
		waitToMove = true;
	else if (actualDirection == LEFT) {
		Vector2D aux = posCasilla + Vector2D(-1, 0);
		if (aux.getX() < 0)
			waitToMove = true;
	} /* && !checkIfTileWalkable(posCasilla + Vector2D(-1, 0)))*/
	else if (actualDirection == DOWN && !checkIfTileWalkable(posCasilla + Vector2D(0, 1)))
		waitToMove = true;
	else if (actualDirection == UP) {
		Vector2D aux = posCasilla + Vector2D(0, -1);
		if (aux.getY() < 0) {
			waitToMove = true;
		}
	}/* && !checkIfTileWalkable(posCasilla + Vector2D(0, -1)))*/
}
