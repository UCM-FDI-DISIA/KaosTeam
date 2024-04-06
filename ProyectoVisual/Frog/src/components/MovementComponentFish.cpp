#include "MovementComponentFish.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include "../scenes/RoomScene.h"

void MovementComponentFish::update() {
	//if (!isMoving && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime) {
	//	lastTimeMoved = DataManager::GetInstance()->getFrameTime();
	//	if (casillaActual == casillaSalto) {
	//		isJumping = true;
	//	}
	//		

	//	switch (actualDirection)
	//	{
	//	case RIGHT: {
	//		velocity = Vector2D(1, 0);
	//		framesPerJump = 4 + velocity.magnitude() * 3;
	//		anim->playAnimation("RIGHT");
	//	}
	//			  break;
	//	case LEFT:
	//	{
	//		velocity = Vector2D(-1, 0);
	//		framesPerJump = 4 + velocity.magnitude() * 3;
	//		anim->playAnimation("LEFT");
	//	}
	//	break;
	//	default:
	//		break;
	//	}
	//	isMoving = true;
	//}
	//else if (isMoving && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > movementFrameRate) {
	//	lastTimeMoved = DataManager::GetInstance()->getFrameTime();
	//
	//	int t = ent->getScene()->getMapReader()->getTileSize();
	//	framesMoved++;
	//	offsetInCasilla.setX(offsetInCasilla.getX() + t / framesPerJump * velocity.getX());
	//	if (isJumping) {

	//		offsetInCasilla.setY(-t / 2 * sin(3.14 / framesPerJump * framesMoved));
	//		if (actualDirection == RIGHT) {
	//			anim->playAnimation("JUMP_RIGHT");
	//		}
	//		else if (actualDirection == LEFT) {
	//			anim->playAnimation("JUMP_LEFT");
	//		}
	//	}

	//	if (offsetInCasilla.getX() * velocity.normalize().getX() >= t / 2 ||
	//		offsetInCasilla.getY() * velocity.normalize().getY() >= t / 2) //si se mueve mas de media casilla, est� en la casilla siguiente
	//	{
	//		//changePos(velocity.normalize() + posCasilla);
	//		if (actualDirection == LEFT || actualDirection == RIGHT)
	//			offsetInCasilla.setX(offsetInCasilla.getX() * -1);
	//		else
	//			offsetInCasilla.setY(offsetInCasilla.getY() * -1);
	//	}
	//	/*else {
	//		offsetInCasilla.setX(offsetInCasilla.getX() + t / framesPerJump * velocity.getX());
	//	}*/

	//	if (framesMoved == framesPerJump) {
	//		//posCasilla = destCasilla;
	//		offsetInCasilla = { 0,0 };
	//		framesMoved = 0;
	//		isMoving = false;
	//		isJumping = false;
	//		casillaActual++;
	//		if (casillaActual == limite - 1)  changeDirection();
	//	}
	//}
	if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime)
	{
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		//si la casilla actual es donde debe saltar
		if (casillaActual == casillaSalto) {
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
		else {
			//se mueve una casilla en la direccion correspondiente
			switch (actualDirection)
			{
			case RIGHT:
				anim->playAnimation("RIGHT");
				transform->setCasilla(transform->getCasilla() + Vector2D(1, 0));
				break;
			case LEFT:
				anim->playAnimation("LEFT");
				transform->setCasilla(transform->getCasilla() + Vector2D(-1, 0));
				break;
			default:
				break;
			}
			casillaActual++;
		}
		
		//si la casilla en la que se encuentra es la del borde (-1 pq se empieza a contar en 0) 
		//se cambia de direccion
		if (casillaActual == limite - 1) changeDirection();
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