#include "MovementComponentHeadRoach.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../scenes/RoomScene.h"

MovementComponentHeadRoach::MovementComponentHeadRoach(bool move) : canMove(move), direction(NONE), hitted(false) {
	timerForDelete.pause(); //pausamos timer de explosi�n (solo se activa cuando la bomba ha chocado con algo)
}

MovementComponentHeadRoach::~MovementComponentHeadRoach() {
	moveFrog = nullptr;
}

void MovementComponentHeadRoach::initComponent() {
	//Obtenemos componentes necesarios
	moveFrog = static_cast<MovementComponentFrog*>(ent->getScene()->getPlayer()->getComponent(MOVEMENT_COMPONENT));
	tr = static_cast<TransformComponent*> (ent->getComponent(TRANSFORM_COMPONENT));
	coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));
	direction = moveFrog->getDirection();
	//A�adimos funcion de collider a la cabeza
	coll->GetTransofmCollider()->AddCall([this](Entity* e, Collider c) {checkEntityCollisions(e, c); }); //Añadimos callback
}

void MovementComponentHeadRoach::checkEntityCollisions(Entity* ent, Collider c) {
	if (canMove && ent->getName() != FROG_ENTITY) {
		LifeComponent* lifeEntity = static_cast<LifeComponent*>(ent->getComponent(LIFE_COMPONENT));
		if (lifeEntity != nullptr && !hitted) {
			lifeEntity->hit(1); //bajamos vida de la entidad con la que choca
			velocity = Vector2D(0, 0);//cabeza "quieta", espera a ser eliminada
			timerForDelete.resume();//cuenta atras para eliminarla
			hitted = true;
		}
	}
}
//comprueba si se puede mover en la direccion(que no choque contra paredes)
void MovementComponentHeadRoach::checkCanMove(Vector2D vel) {
	Vector2D aux = tr->getCasilla() + vel;
	if (!checkIfTileWalkable(aux)) {
		velocity = Vector2D(0, 0);
	}
}

//Mueve la cabeza en la direccion dada:
void MovementComponentHeadRoach::moveHead() {
	switch (direction) {
	case Directions::DOWN:
		velocity = Vector2D(0, 0.1);
		checkCanMove(velocity);
		tr->setCasilla(tr->getCasilla() + velocity);
		break;
	case Directions::UP:
		velocity = Vector2D(0, -0.1);
		checkCanMove(velocity);
		tr->setCasilla(tr->getCasilla() + velocity);
		break;
	case Directions::LEFT:
		velocity = Vector2D(-0.1, 0);
		checkCanMove(velocity);
		tr->setCasilla(tr->getCasilla() + velocity);
		break;
	case Directions::RIGHT:
		velocity = Vector2D(0.1, 0);
		checkCanMove(velocity);
		tr->setCasilla(tr->getCasilla() + velocity);
		break;
	default:
		break;
	}
}
void MovementComponentHeadRoach::update() {
	//cuando pase el tiempo de espera para eliminar, se elimina la entidad de la cabeza
	if (timerForDelete.currTime() >= WAIT_DELETE ) {
		ent->getScene()->removeEntity(this->ent);
	}

	if (canMove && !hitted) {
		moveHead();
	}
}


