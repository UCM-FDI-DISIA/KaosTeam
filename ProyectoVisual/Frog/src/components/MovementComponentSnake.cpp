#include "MovementComponentSnake.h"
#include "RenderComponentSnake.h"
#include "AttackComponentSnake.h"
#include "../scenes/RoomScene.h"
#include "../ecs/Entity.h"

void MovementComponentSnake::update()
{
	if (DataManager::GetInstance()->getFrameTime() - lastTimeAction > coolDownTime) {

		lastTimeAction = DataManager::GetInstance()->getFrameTime(); //Actualizamos tiempo de acci�n

		//La serpeinte va a estar rotando constantemente
		//... L�gica de rotaci�n aqu�
		//Primero comprobamos si est� rotando la serpiente o no
		if (isRotate) {
			rotateSnake(); // Rotamos serpiente
			searchFrog();  // Buscamos a la rana en la dir de rotacion
		}
			

		//En el momento que la rana este en el �rea de visi�n la serpiente ataca
		// desactivamos rotaci�n y activamos ataque


		//Estiramos serpiente hasta la posici�n de la rana y atacamos

		//Vuelve a su posicion original y desactivamos ataque
	}
}

void MovementComponentSnake::rotateSnake() {
	//Cambiamos direcci�n de rotaci�n
	switch (currentDirection) {
	case Direction::DOWN_ROT:
		currentDirection = Direction::LEFT_ROT;
		//anim->playAnimation("LEFT_ROTATION");
		break;
	case Direction::LEFT_ROT:
		currentDirection = Direction::UP_ROT;
		//anim->playAnimation("IDLE_RIGHT");
		break;
	case Direction::UP_ROT:
		currentDirection = Direction::RIGHT_ROT;
		//(anim->playAnimation("RIGHT_ROTATION");
		break;
	case Direction::RIGHT_ROT:
		currentDirection = Direction::DOWN_ROT;
		//anim->playAnimation("IDLE_LEFT");
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
		////Comprobamos si la direccion es valida
		if (currentDirection == DOWN_ROT) {
			if ((distance.getY() <= attackDistance) && (distance.getY() > 0)) { //Si esta en el rango de ataque...
				std::cout << "SNAKE ATACA abajo" << std::endl;
				static_cast<AttackComponentSnake*>(ent->getComponent(ATTACK_COMPONENT))->attack();
			}
		}
		else if (currentDirection == UP_ROT) {
			if ((distance.getY() >= -attackDistance) && (distance.getY() < 0)) {
				std::cout << "SNAKE ATACA arriba" << std::endl;
				static_cast<AttackComponentSnake*>(ent->getComponent(ATTACK_COMPONENT))->attack();
			}
		}
	}
	else if (getPosition().getY() == playerPos->getY()) {
		if (currentDirection == RIGHT_ROT) {
			if ((distance.getX() <= attackDistance) && (distance.getX() > 0)) {
				std::cout << "SNAKE ATACA derecha" << std::endl;
				static_cast<AttackComponentSnake*>(ent->getComponent(ATTACK_COMPONENT))->attack();
			}
		}
		else if (currentDirection == LEFT_ROT) {
			if ((distance.getX() >= -attackDistance) && (distance.getX() < 0)) {
				std::cout << "SNAKE ATACA izquierda" << std::endl; 
				static_cast<AttackComponentSnake*>(ent->getComponent(ATTACK_COMPONENT))->attack();
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