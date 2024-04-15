#include "MovementComponentBomb.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../scenes/RoomScene.h"

MovementComponentBomb::MovementComponentBomb() : isLaunched(true), direction(DOWN) {
}

void MovementComponentBomb::initComponent() {
	//Obtenemos componentes
	moveFrog = static_cast<MovementComponentFrog*>(ent->getScene()->getPlayer()->getComponent(TRANSFORM_COMPONENT));
	animator = static_cast<AnimationComponent*>(ent->getComponent(ANIMATION_COMPONENT));
	tr = static_cast<TransformComponent*> (ent->getComponent(TRANSFORM_COMPONENT));
}

//Mueve la bomba en la direccion dada:
void MovementComponentBomb::moveBomb(Directions dir) {
	switch (dir) {
	case DOWN:
		tr->setCasilla(tr->getCasilla() + Vector2D(0, 1));
		break;
	case UP:
		tr->setCasilla(tr->getCasilla() + Vector2D(0, -1));
		break;
	case LEFT:
		tr->setCasilla(tr->getCasilla() + Vector2D(-1, 0));
		break;
	case RIGHT:
		tr->setCasilla(tr->getCasilla() + Vector2D(1, 0));
		break;
	default:
		break;
	}
	isLaunched = false;
	animator->playAnimation("BOMB_IDLE");
	std::cout << "BOMBA SE MUEVE" << std::endl;
}


void MovementComponentBomb::update() {
	if (isLaunched) //Si se activa la flag de que se ha lanzado la bomba
		direction = moveFrog->getDirection(); //Obtenemos direccion a la que mira la rana

	moveBomb(direction); //movemos bomba en la dirección dada
}


