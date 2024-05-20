#include "MovementComponentBlackAnt.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include "../scenes/RoomScene.h"
#include "TransformComponent.h"

MovementComponentBlackAnt::MovementComponentBlackAnt(AnimationComponent* a) : MovementComponent(), lastTimeMoved(SDL_GetTicks()), anim(a), rand_(sdlutils().rand())
{
	actualDirection = RIGHT;
	anim->playAnimation("RIGHT");
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
	targetTransformComp = nullptr;
	anim = nullptr;
}
void MovementComponentBlackAnt::initComponent() {
	targetTransformComp = static_cast<TransformComponent*>(ent->getScene()->getPlayer()->getComponent(TRANSFORM_COMPONENT));
	playerPosition = targetTransformComp->getCasilla();
	tr = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
}

void MovementComponentBlackAnt::update() {

	//si no se esta moviendo, ni esta inmovil, ni esta esperando a atacar
	//segun la direccion se cambia la animacion y la velocidad, esta tambien depende de si la hormiga esta en estado de atacar a la rana
	if (!waitToAttack && !waitToMove && !isMoving && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime && canMove) {
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		playerPosition = targetTransformComp->getCasilla();
		switch (actualDirection)
		{
		case RIGHT: {
			anim->playAnimation("RIGHT");
			if (isAtacking) {
				velocity = Vector2D(diff, 0);
				framesPerMove = 2 + velocity.magnitude() * 3;
			}
			else {
				velocity = Vector2D(1, 0);
				framesPerMove = 4 + velocity.magnitude() * 3;
			}
		}
		break;
		case LEFT:
		{
			anim->playAnimation("LEFT");
			if (isAtacking) {
				velocity = Vector2D(diff, 0);
				framesPerMove = 2 + velocity.magnitude() * 3;
			}
			else {
				velocity = Vector2D(-1, 0);
				framesPerMove = 4 + velocity.magnitude() * 3;
			}
		}
		break;
		case UP:
		{
			anim->playAnimation("UP");
			if (isAtacking) {
				velocity = Vector2D(0, diff);	
				framesPerMove = 2 + velocity.magnitude() * 3;
			}
			else {
				velocity = Vector2D(0, -1);
				framesPerMove = 4 + velocity.magnitude() * 3;
			}
		}
		break;
		case DOWN:
		{
			anim->playAnimation("DOWN");
			if (isAtacking) {
				velocity = Vector2D(0, diff);
				framesPerMove = 4 + velocity.magnitude() * 3;;
			}
			else {
				velocity = Vector2D(0, 1);
				framesPerMove = 4 + velocity.magnitude() * 3;
			}
		}
		break;
		default:
			break;
		}
		isMoving = true;
	}
	//si esta en estado de moverse, se mueve en la direccion correspondiente
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
			std::cout << tr->getCasilla().getX() << " " << tr->getCasilla().getX() << std::endl;
			tr->setCasilla(tr->getCasilla() + velocity);
			tr->setOffset({ 0,0 });
			framesMoved = 0;
			isMoving = false;
			//si estaba atacando deja de atacar y comprueba que no se haya chocado con una pared
			if (isAtacking) {
				diff = 0;
				isAtacking = false;
				checkCollisionWall();
			}
			//comprueba si debe atacar
			bool attack = isPlayerNear();
			//si no tiene que atacar, cambia de direccion
			if (!attack)
				changeDirection();
		}
	}
	//si tiene que esperar para atacar
	else if (waitToAttack) {
		Uint32 currentTime = DataManager::GetInstance()->getFrameTime();
		if ((currentTime - lastTimeMoved) > waitTimeAttack) {
			isAtacking = true;
			waitToAttack = false;
			lastTimeMoved = currentTime;
		}
	}
	//si tiene que esperar para moverse por estar inmovil
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
//comprueba si esta el jugador cerca ya sea en la misma columna o fila de nuestro sistema por casillas y dependiendo de su direccion actual
bool MovementComponentBlackAnt::isPlayerNear() {
	if (playerPosition.getY() == tr->getCasilla().getY()) {

		if (actualDirection != LEFT && playerPosition.getX() - tr->getCasilla().getX() <= range && playerPosition.getX() - tr->getCasilla().getX() > 0) {
			actualDirection = RIGHT;
			diff = playerPosition.getX() - tr->getCasilla().getX();
			waitToAttack = true;
		}
		else if (!waitToAttack && actualDirection != RIGHT && tr->getCasilla().getX() - playerPosition.getX() <= range && tr->getCasilla().getX() - playerPosition.getX() > 0) {
			actualDirection = LEFT;
			diff = playerPosition.getX() - tr->getCasilla().getX();
			waitToAttack = true;
		}
	}
	else if (!waitToAttack && playerPosition.getX() == tr->getCasilla().getX()) {
		if (actualDirection != UP && playerPosition.getY() - tr->getCasilla().getY() <= range && playerPosition.getY() - tr->getCasilla().getY() > 0) {
			actualDirection = DOWN;
			waitToAttack = true;
			diff = playerPosition.getY() - tr->getCasilla().getY();
		}
		else if (!waitToAttack && actualDirection != DOWN && tr->getCasilla().getY() - playerPosition.getY() <= range && tr->getCasilla().getY() - playerPosition.getY() > 0) {
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
