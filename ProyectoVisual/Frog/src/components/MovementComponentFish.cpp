#include "MovementComponentFish.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include "../scenes/RoomScene.h"

void MovementComponentFish::update() {
	if (!isMoving && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime) {
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		if (casillaActual == casillaSalto) {
			isJumping = true;
			switch (actualDirection)
			{
			//se mueve media casilla hacia arriba y media casilla hacia abajo en la direccion correspondiente
			//cuando ha terminado de saltar es cuando termina el movimiento completo (casillaActual++)
			case RIGHT:
				if (!isJumping) {
					isJumping = true;
					transform->setCasilla(transform->getCasilla() + Vector2D(0.5, -1));
					anim->playAnimation("JUMP_RIGHT");
				}
				else if (isJumping) {
					isJumping = false;
					transform->setCasilla(transform->getCasilla() + Vector2D(0.5, 1));
					casillaActual++;
					anim->playAnimation("RIGHT");
				}
				
				break;
			case LEFT:
				if (!isJumping) {
					isJumping = true;
					transform->setCasilla(transform->getCasilla() + Vector2D(-0.5, -1));
					anim->playAnimation("JUMP_LEFT");
				}
				else if (isJumping) {
					isJumping = false;
					transform->setCasilla(transform->getCasilla() + Vector2D(-0.5, 1));
					casillaActual++;
					anim->playAnimation("LEFT");
				}
				break;
			default:
				break;
			}
		}
		switch (actualDirection)
		{
		case RIGHT: {
			velocity = Vector2D(1, 0);
			//framesPerMove = 4 + velocity.magnitude() * 3;
			if (isJumping) 
				anim->playAnimation("JUMP_RIGHT");
			else 
				anim->playAnimation("RIGHT");
		}
				  break;
		case LEFT:
		{
			velocity = Vector2D(-1, 0);
			//framesPerMove = 4 + velocity.magnitude() * 3;
			if(isJumping)
				anim->playAnimation("JUMP_LEFT");
			else
				anim->playAnimation("LEFT");
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
		tr->setOffsetX(tr->getOffset().getX() + t / framesPerMove * velocity.getX());
		if (isJumping) {
			tr->setOffsetY(-t / 2 * sin(3.14 / framesPerMove * framesMoved));
		}
		if (framesMoved == framesPerMove) {
			
			tr->setCasilla(tr->getCasilla() + velocity);
			offsetInCasilla = { 0,0 };
			framesMoved = 0;
			isMoving = false;
			isJumping = false;

			casillaActual++;
			if (casillaActual == limite - 1)  changeDirection();
		}
	}
}
//metodo para cambiar de direccion y todo lo que conlleva eso
void MovementComponentFish::changeDirection() {
	//cambiar direccion
	if (actualDirection == RIGHT) actualDirection = LEFT;
	else if (actualDirection == LEFT) actualDirection = RIGHT;
	//restaurar la casilla actual a 0
	casillaActual = 0;
	//volver a elegir aleatoriamente la casilla en la que va a saltar
	casillaSalto = rand_.nextInt(0, limite - 1);
}