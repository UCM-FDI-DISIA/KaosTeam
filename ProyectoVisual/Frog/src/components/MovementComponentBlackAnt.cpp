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
		if (framesMoved == framesPerMove) {
			posCasilla = posCasilla + velocity;
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
		if (checkIfTileWalkable(aux)) {
			actualDirection = LEFT;
		}
		else
			changeDirection();
	}
		  break;
	case 2: {
		Vector2D aux = posCasilla + Vector2D(0, -1);
		if (checkIfTileWalkable(aux)) {
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
	if (playerPosition.getY() == posCasilla.getY()) {

		if (actualDirection != LEFT && playerPosition.getX() - posCasilla.getX() <= range) {
			actualDirection = RIGHT;
			diff = playerPosition.getX() - posCasilla.getX();
			waitToAttack = true;
		}
		else if (!waitToAttack && actualDirection != RIGHT && posCasilla.getX() - playerPosition.getX() <= range) {
			actualDirection = LEFT;
			diff = playerPosition.getX() - posCasilla.getX();
			waitToAttack = true;
		}
	}
	else if (!waitToAttack && playerPosition.getX() == posCasilla.getX()) {
		if (actualDirection != UP && playerPosition.getY() - posCasilla.getY() <= range) {
			actualDirection = DOWN;
			waitToAttack = true;
			diff = playerPosition.getY() - posCasilla.getY();
		}
		else if (!waitToAttack && actualDirection != DOWN && posCasilla.getY() - playerPosition.getY() <= range) {
			actualDirection = UP;
			waitToAttack = true;
			diff = playerPosition.getY() - posCasilla.getY();
		}
	}
	return waitToAttack;
}
void MovementComponentBlackAnt::checkCollisionWall() {
	//comprobar si da con la pared y si es asi waitToMove = true
	if (actualDirection == RIGHT && !checkIfTileWalkable(posCasilla + Vector2D(1, 0)))
		waitToMove = true;
	else if (actualDirection == LEFT && !checkIfTileWalkable(posCasilla + Vector2D(-1, 0))) 
			waitToMove = true;
	else if (actualDirection == DOWN && !checkIfTileWalkable(posCasilla + Vector2D(0, 1)))
		waitToMove = true;
	else if (actualDirection == UP && !checkIfTileWalkable(posCasilla + Vector2D(0, -1))) 
			waitToMove = true;
}
