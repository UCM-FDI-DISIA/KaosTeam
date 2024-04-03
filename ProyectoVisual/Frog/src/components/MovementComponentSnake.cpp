#include "MovementComponentSnake.h"
#include "../scenes/RoomScene.h"
#include "../ecs/Entity.h"

void MovementComponentSnake::update()
{
	if (DataManager::GetInstance()->getFrameTime() - lastTimeAction > coolDownTime) {

		lastTimeAction = DataManager::GetInstance()->getFrameTime(); //Actualizamos tiempo de acción

		//La serpeinte va a estar rotando constantemente
		//... Lógica de rotación aquí
		//Primero comprobamos si está rotando la serpiente o no
		if (isRotate) {
			rotateSnake(); //Rotamos serpiente
			searchFrog();  // Buscamos a la rana en la dir de rotacion
		}
			

		//En el momento que la rana este en el área de visión la serpiente ataca
		// desactivamos rotación y activamos ataque


		//Estiramos serpiente hasta la posición de la rana y atacamos

		//Vuelve a su posicion original y desactivamos ataque
	}
}

void MovementComponentSnake::rotateSnake() {
	//Cambiamos dirección de rotación
	switch (currentDirection) {
	//case DOWN:
	//	currentDirection = LEFT;
	//	anim->playAnimation("LEFT_ROTATION");
	//	break;
	case LEFT:
		currentDirection = RIGHT;
		anim->playAnimation("RIGHT_ROTATION");
		break;
	/*case UP:
		currentDirection = RIGHT;
		anim->playAnimation("RIGHT_ROTATION");
		break;*/
	case RIGHT:
		currentDirection = LEFT;
		anim->playAnimation("LEFT_ROTATION");
		break;
	}
}

void MovementComponentSnake::searchFrog() {
	//Obtenemos posicion del jugador
	if (playerPos == nullptr)
		playerPos = static_cast<MovementComponent*>(ent->getScene()->getPlayer()->getComponent(MOVEMENT_COMPONENT))->getPosPointer();

	//calculamos distancia
	Vector2D distance = *playerPos - getPosition();

	std::cout << "(" << playerPos->getX() << " , " << playerPos->getY() << ")" << "PlayerPosition" << std::endl;
	std::cout << "(" << getPosition().getX() << " , " << getPosition().getY() << ")" << "SnakePosition" << std::endl;
	std::cout << "(" << distance.getX() << " , " << distance.getY() << ")" << "DISTANCE" << std::endl;
	std::cout << " " << std::endl;

	//Identificamos la col/fil en la que esta la serpiente y la rana 
	if (getPosition().getX() == playerPos->getX()) {
		//Comprobamos si la direccion es valida
		if (currentDirection == DOWN) {
			if ((distance.getY() <= attackDistance) && (distance.getY() > 0)) { //Si esta en el rango de ataque...
				std::cout << "SNAKE ATACA abajo" << std::endl;
			}
		}
		else if (currentDirection == UP) {
			if ((distance.getY() >= -attackDistance) && (distance.getY() < 0)) {
				std::cout << "SNAKE ATACA arriba" << std::endl;
			}
		}
	}
	else if (getPosition().getY() == playerPos->getY()) {
		if (currentDirection == RIGHT) {
			if ((distance.getX() <= attackDistance) && (distance.getX() > 0)) {
				std::cout << "SNAKE ATACA derecha" << std::endl;
			}
		}
		else if (currentDirection == LEFT) {
			if ((distance.getX() >= -attackDistance) && (distance.getX() < 0)) {
				std::cout << "SNAKE ATACA izquierda" << std::endl;
			}
		}
	}


	//switch (currentDirection) {
	//case DOWN:
	//	if ((distance.getY() <= attackDistance) && (distance.getY() > 0) && (getPosition().getX() == playerPos->getX())) {
	//		std::cout << "SNAKE ATACA abajo" << std::endl;
	//		isRotate = false;
	//	}
	//	break;
	//case UP:
	//	if ((distance.getY() >= -attackDistance) && (distance.getY() < 0) && (getPosition().getX() == playerPos->getX())) {
	//		std::cout << "SNAKE ATACA arriba" << std::endl;
	//		isRotate = false;
	//	}
	//	break;
	//case RIGHT:
	//	//Si esta en el rango de distancia y estan en la misma fila... ataca
	//	if ((distance.getX() <= attackDistance) && (distance.getX() > 0) && (getPosition().getY() == playerPos->getY())) {
	//		std::cout << "SNAKE ATACA derecha" << std::endl;
	//		isRotate = false;
	//	}
	//	break;
	//case LEFT:
	//	if ((distance.getX() >= -attackDistance) && (distance.getX() < 0) && (getPosition().getY() == playerPos->getY())) {
	//		std::cout << "SNAKE ATACA izquierda" << std::endl;
	//		isRotate = false;
	//	}
	//	break;
	//}

}
