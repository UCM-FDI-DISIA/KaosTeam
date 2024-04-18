#include "MovementComponentSnake.h"
#include "RenderComponentSnake.h"
#include "AttackComponentSnake.h"
#include "../scenes/RoomScene.h"
#include "../ecs/Entity.h"


MovementComponentSnake::MovementComponentSnake(AnimationComponent* a) :
	MovementComponent(), anim(a),
	lastTimeAction(DataManager::GetInstance()->getFrameTime()), coolDownTime(1000),
	isRotate(true), isAttack(false),
	currentDirection(Direction::RIGHT_ROT), attackDistance(2) {
}

void MovementComponentSnake::update()
{
	if (DataManager::GetInstance()->getFrameTime() - lastTimeAction > coolDownTime) {

		lastTimeAction = DataManager::GetInstance()->getFrameTime(); //Actualizamos tiempo de acción

		//La serpeinte va a estar rotando constantemente
		//... Lógica de rotación aquí
		//Primero comprobamos si está rotando la serpiente o no
		if (isRotate) {
			rotateSnake(); // Rotamos serpiente
			searchFrog();  // Buscamos a la rana en la dir de rotacion
			std::cout << "ROTANDO" << std::endl;
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
	playerPos = targetTransformComp->getCasilla();

	//calculamos distancia
	Vector2D distance = playerPos - tr->getCasilla();

	std::cout << "(" << playerPos.getX() << " , " << playerPos.getY() << ")" << "PlayerPosition" << std::endl;
	std::cout << "(" << tr->getCasilla().getX() << " , " << tr->getCasilla().getY() << ")" << "SnakePosition" << std::endl;
	std::cout << "(" << distance.getX() << " , " << distance.getY() << ")" << "DISTANCE" << std::endl;
	std::cout << " " << std::endl;

	//Identificamos la col/fil en la que esta la serpiente y la rana 
	if (tr->getCasilla().getX() == playerPos.getX()) {
		////Comprobamos si la direccion es valida
		if (currentDirection == DOWN_ROT) {
			if ((distance.getY() <= attackDistance) && (distance.getY() > 0)) { //Si esta en el rango de ataque...
				std::cout << "SNAKE ATACA abajo" << std::endl;
				ent->getComponent<AttackComponentSnake>(ATTACK_COMPONENT)->attack();
			}
		}
		else if (currentDirection == UP_ROT) {
			if ((distance.getY() >= -attackDistance) && (distance.getY() < 0)) {
				std::cout << "SNAKE ATACA arriba" << std::endl;
				ent->getComponent<AttackComponentSnake>(ATTACK_COMPONENT)->attack();
			}
		}
	}
	else if (tr->getCasilla().getY() == playerPos.getY()) {
		if (currentDirection == RIGHT_ROT) {
			if ((distance.getX() <= attackDistance) && (distance.getX() > 0)) {
				std::cout << "SNAKE ATACA derecha" << std::endl;
				ent->getComponent<AttackComponentSnake>(ATTACK_COMPONENT)->attack();
			}
		}
		else if (currentDirection == LEFT_ROT) {
			if ((distance.getX() >= -attackDistance) && (distance.getX() < 0)) {
				std::cout << "SNAKE ATACA izquierda" << std::endl; 
				ent->getComponent<AttackComponentSnake>(ATTACK_COMPONENT)->attack();
			}
		}
	}
}

void MovementComponentSnake::initComponent() {
	targetTransformComp = ent->getScene()->getPlayer()->getComponent<TransformComponent>(TRANSFORM_COMPONENT);
	tr = ent->getComponent<TransformComponent>(TRANSFORM_COMPONENT);
}

