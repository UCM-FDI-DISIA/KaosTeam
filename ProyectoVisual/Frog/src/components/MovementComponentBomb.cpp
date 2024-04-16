#include "MovementComponentBomb.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../scenes/RoomScene.h"

MovementComponentBomb::MovementComponentBomb() : isLaunched(true), direction(NONE) {
}

void MovementComponentBomb::initComponent() {
	//Obtenemos componentes
	moveFrog = static_cast<MovementComponentFrog*>(ent->getScene()->getPlayer()->getComponent(MOVEMENT_COMPONENT));
	animator = static_cast<AnimationComponent*>(ent->getComponent(ANIMATION_COMPONENT));
	tr = static_cast<TransformComponent*> (ent->getComponent(TRANSFORM_COMPONENT));
}

//Mueve la bomba en la direccion dada:
void MovementComponentBomb::moveBomb(Directions dir) {
	switch (dir) {
	case Directions::DOWN:
		tr->setCasilla(tr->getCasilla() + Vector2D(0, 0.005));
		std::cout << "BOMBA SE ABAJO" << std::endl;
		break;
	case Directions::UP:
		tr->setCasilla(tr->getCasilla() + Vector2D(0, -0.005));
		std::cout << "BOMBA SE ARRIBA" << std::endl;
		break;
	case Directions::LEFT:
		tr->setCasilla(tr->getCasilla() + Vector2D(-0.005, 0));
		std::cout << "BOMBA SE IZQDA" << std::endl;
		break;
	case Directions::RIGHT:
		tr->setCasilla(tr->getCasilla() + Vector2D(0.005, 0));
		std::cout << "BOMBA SE DERECHA" << std::endl;
		break;
	default:
		break;
	}
	isLaunched = false;
	animator->playAnimation("BOMB_IDLE");
}


void MovementComponentBomb::update() {
	if (isLaunched) { //Si se activa la flag de que se ha lanzado la bomba
		direction = moveFrog->getDirection(); //Obtenemos direccion a la que mira la rana
	}
	moveBomb(direction); //movemos bomba en la dirección dada
}


