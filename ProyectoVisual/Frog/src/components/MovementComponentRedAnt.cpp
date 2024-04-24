#include "MovementComponentRedAnt.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include "../scenes/RoomScene.h"


MovementComponentRedAnt::MovementComponentRedAnt(AnimationComponent* a, MovementComponentFrog* target) : MovementComponent(), lastTimeMoved(SDL_GetTicks()), anim(a), rand_(sdlutils().rand())
{
	actualDirection = RIGHT;
	//anim->playAnimation("RIGHT");
	waitTime = 500;
	movementFrameRate = 30;
	framesPerMove = 6;
	framesMoved = 0;
	isMoving = false;
	escape = false;
	range = 2;
};

void MovementComponentRedAnt::initComponent() {
	targetTransformComp = static_cast<TransformComponent *>( ent->getScene()->getPlayer()->getComponent(TRANSFORM_COMPONENT));
	playerPosition = targetTransformComp->getCasilla();
}

void MovementComponentRedAnt::canMove(Vector2D vel, Direction dir) {
	Vector2D aux = tr->getCasilla() + vel;
	switch (dir) {
	case MovementComponentRedAnt::RIGHT:
	{
		if (checkIfTileWalkable(aux)) {
			velocity = Vector2D(1, 0);
		}
		else {
			velocity = Vector2D(0, 0);
		}
	}
	break;
	case MovementComponentRedAnt::LEFT:
	{
		if (checkIfTileWalkable(aux)) {
			velocity = Vector2D(-1, 0);
		}
		else {
			velocity = Vector2D(0, 0);
		}
	}
	break;
	case MovementComponentRedAnt::UP:
	{
		if (checkIfTileWalkable(aux)) {
			velocity = Vector2D(0, -1);
		}
		else {
			velocity = Vector2D(0, 0);
		}
	}
	break;
	case MovementComponentRedAnt::DOWN:
	{
		if (checkIfTileWalkable(aux)) {
			velocity = Vector2D(0, 1);
		}
		else {
			velocity = Vector2D(0, 0);
		}
	}
	break;
	default:
		break;
	}
}

void MovementComponentRedAnt::update() {

	if (!isMoving && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime) {
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		playerPosition = targetTransformComp->getCasilla();
		switch (actualDirection)
		{
		case RIGHT: {
			canMove(Vector2D(1, 0), RIGHT);
			if (escape) {
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
			canMove(Vector2D(-1, 0), LEFT);
			if (escape) {
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
			canMove(Vector2D(0, -1), UP);
			if (escape) {
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
			canMove(Vector2D(0, 1), DOWN);
			if (escape) {
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
			tr->setOffsetX(tr->getOffset().getX() + t / framesPerMove * velocity.getX());
		}
		else {
			tr->setOffsetY(tr->getOffset().getY() + t / framesPerMove * velocity.getY());
		}
		if (framesMoved == framesPerMove) {
			tr->setCasilla(tr->getCasilla() + velocity);
			tr->setOffset ({ 0,0 });
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
		Vector2D aux = tr->getCasilla() + Vector2D(1, 0);
		if (checkIfTileWalkable(aux)) {
			actualDirection = RIGHT;
		}
		else
			changeDirection();
	}
		  break;
	case 1: {
		Vector2D aux = tr->getCasilla() + Vector2D(-1, 0);
		if (checkIfTileWalkable(aux)) {
			actualDirection = LEFT;
		}
		else
			changeDirection();
	}
		  break;
	case 2: {
		Vector2D aux = tr->getCasilla() + Vector2D(0, -1);
		if (checkIfTileWalkable(aux)) {
			actualDirection = UP;
		}
		else
			changeDirection();
	}
		  break;
	case 3: {
		Vector2D aux = tr->getCasilla() + Vector2D(0, 1);
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
	if (playerPosition.getY() == tr->getCasilla().getY()) {
		if (playerPosition.getX() - tr->getCasilla().getX() <= range && playerPosition.getX() - tr->getCasilla().getX() > 0) {
			if (actualDirection == RIGHT) actualDirection = LEFT;
			escape = true;
		}
		else if (!escape && tr->getCasilla().getX() - playerPosition.getX() <= range && tr->getCasilla().getX() - playerPosition.getX() > 0) {
			if (actualDirection == LEFT) actualDirection = RIGHT;
			escape = true;
		}
	}
	else if (!escape && playerPosition.getX() == tr->getCasilla().getX()) {
		if (playerPosition.getY() - tr->getCasilla().getY() <= range && playerPosition.getY() - tr->getCasilla().getY() > 0) {
			if (actualDirection == DOWN) actualDirection = UP;
			escape = true;
		}
		else if (!escape && tr->getCasilla().getY() - playerPosition.getY() <= range && tr->getCasilla().getY() - playerPosition.getY() > 0) {
			if (actualDirection == UP) actualDirection = DOWN;
			escape = true;
		}
	}
}
