#include "MovementComponentCockroach.h"
#include "../scenes/RoomScene.h"
#include "../components/TransformComponent.h"
#include "../sdlutils/RandomNumberGenerator.h"
MovementComponentCockroach::MovementComponentCockroach(AnimationComponent* a) : MovementComponent(), lastTimeMoved(SDL_GetTicks()), anim(a), rand_(sdlutils().rand())
{
	actualDirection = RIGHT;
	anim->playAnimation("RIGHT");
	waitTime = 500;
	movementFrameRate = 30;
	framesPerMove = 6;
	framesMoved = 0;
	isMoving = false;
	isAttacked = false;
}
MovementComponentCockroach::~MovementComponentCockroach() {
	anim = nullptr;
}
void MovementComponentCockroach::initComponent() {
	tr = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
}

void MovementComponentCockroach::update() {

	/*if (!isMoving && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime) {
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		switch (actualDirection)
		{
		case RIGHT: {
			velocity = Vector2D(1, 0);
			anim->playAnimation("RIGHT");
			framesPerMove = 4 + velocity.magnitude() * 3;
		}
				  break;
		case LEFT:
		{
			velocity = Vector2D(-1, 0);
			anim->playAnimation("LEFT");
			framesPerMove = 4 + velocity.magnitude() * 3;
		}
		break;
		case UP:
		{
			velocity = Vector2D(0, -1);
			anim->playAnimation("UP");
			framesPerMove = 4 + velocity.magnitude() * 3;
		}
		break;
		case DOWN:
		{
			velocity = Vector2D(0, 1);
			anim->playAnimation("DOWN");
			framesPerMove = 4 + velocity.magnitude() * 3;
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
			changeDirection();
		}
	}*/
}
//metodo para cambiar de direccion y todo lo que conlleva eso
void MovementComponentCockroach::changeDirection() {
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