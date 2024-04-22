#include "MovementComponentBlackAnt.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include "../scenes/RoomScene.h"
#include "../components/TransformComponent.h"

MovementComponentBlackAnt::MovementComponentBlackAnt(AnimationComponent* a) : MovementComponent(), lastTimeMoved(SDL_GetTicks()), anim(a), rand_(sdlutils().rand())
{
	actualDirection = RIGHT;
	//anim->playAnimation("RIGHT");
	waitTime = 500;
	movementFrameRate = 30;
	framesPerMove = 6;
	framesMoved = 0;
	isAtacking = false;
	isMoving = false;
	waitTimeAttack = 1000;
	immobileTime = 2000;
	range = 3;
	waitToAttack = false;
	waitToMove = false;
	diff = 0;
};

MovementComponentBlackAnt::~MovementComponentBlackAnt() {
	delete targetTransformComp;
	targetTransformComp = nullptr;
	delete anim;
	anim = nullptr;
}
void MovementComponentBlackAnt::initComponent() {
	targetTransformComp = static_cast<TransformComponent*>(ent->getScene()->getPlayer()->getComponent(TRANSFORM_COMPONENT));
	playerPosition = targetTransformComp->getCasilla();
}

void MovementComponentBlackAnt::update() {

	if (!waitToAttack && !waitToMove && !isMoving && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime) {
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		playerPosition = targetTransformComp->getCasilla();
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
			tr->setOffsetX(tr->getOffset().getX() + t / framesPerMove * velocity.getX());
		}
		else {
			tr->setOffsetY(tr->getOffset().getY() + t / framesPerMove * velocity.getY());
		}
		if (framesMoved == framesPerMove) {
			tr->setCasilla(tr->getCasilla() + velocity);
			tr->setOffset({ 0,0 });
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
bool MovementComponentBlackAnt::isPlayerNear() {
	if (playerPosition.getY() == tr->getCasilla().getY()) {

		if (actualDirection != LEFT && playerPosition.getX() - tr->getCasilla().getX() <= range) {
			actualDirection = RIGHT;
			diff = playerPosition.getX() - tr->getCasilla().getX();
			waitToAttack = true;
		}
		else if (!waitToAttack && actualDirection != RIGHT && tr->getCasilla().getX() - playerPosition.getX() <= range) {
			actualDirection = LEFT;
			diff = playerPosition.getX() - tr->getCasilla().getX();
			waitToAttack = true;
		}
	}
	else if (!waitToAttack && playerPosition.getX() == tr->getCasilla().getX()) {
		if (actualDirection != UP && playerPosition.getY() - tr->getCasilla().getY() <= range) {
			actualDirection = DOWN;
			waitToAttack = true;
			diff = playerPosition.getY() - tr->getCasilla().getY();
		}
		else if (!waitToAttack && actualDirection != DOWN && tr->getCasilla().getY() - playerPosition.getY() <= range) {
			actualDirection = UP;
			waitToAttack = true;
			diff = playerPosition.getY() - tr->getCasilla().getY();
		}
	}
	return waitToAttack;
}
void MovementComponentBlackAnt::checkCollisionWall() {
	//comprobar si da con la pared y si es asi waitToMove = true
	if (actualDirection == RIGHT && !checkIfTileWalkable(tr->getCasilla() + Vector2D(1, 0)))
		waitToMove = true;
	else if (actualDirection == LEFT && !checkIfTileWalkable(tr->getCasilla() + Vector2D(-1, 0)))
			waitToMove = true;
	else if (actualDirection == DOWN && !checkIfTileWalkable(tr->getCasilla() + Vector2D(0, 1)))
		waitToMove = true;
	else if (actualDirection == UP && !checkIfTileWalkable(tr->getCasilla() + Vector2D(0, -1)))
			waitToMove = true;
}
