#include "MovementComponentBomb.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../scenes/RoomScene.h"

MovementComponentBomb::MovementComponentBomb() : isLaunched(true), direction(NONE) {
}

void MovementComponentBomb::initComponent() {
	//Obtenemos componentes necesarios
	moveFrog = static_cast<MovementComponentFrog*>(ent->getScene()->getPlayer()->getComponent(MOVEMENT_COMPONENT));
	animator = static_cast<AnimationComponent*>(ent->getComponent(ANIMATION_COMPONENT));
	tr = static_cast<TransformComponent*> (ent->getComponent(TRANSFORM_COMPONENT));
	coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));

	 // Aquí envolvemos la función checkEntityShock en un objeto std::function
    //std::function<void(Entity*)> shockCallback = std::bind(&checkEntityShock, this, std::placeholders::_1);
	//coll->AddCall(&shockCallback);
}

//está función, se llamará en cada iteracción del update para detectar con que entity colisiona y hacer las correspondientes acciones
void MovementComponentBomb::checkEntityShock(Entity* ent) {
	/*if (ent.getName()) {
	* 
	* 
	}*/
}

//Mueve la bomba en la direccion dada:
void MovementComponentBomb::moveBomb() {
	switch (direction) {
	case Directions::DOWN:
		velocity = Vector2D(0, 0.01);
		tr->setCasilla(tr->getCasilla() + velocity);
		std::cout << "BOMBA SE ABAJO" << std::endl;
		break;
	case Directions::UP:
		velocity = Vector2D(0, -0.01);
		tr->setCasilla(tr->getCasilla() + velocity);
		std::cout << "BOMBA SE ARRIBA" << std::endl;
		break;
	case Directions::LEFT:
		velocity = Vector2D(-0.01, 0);
		tr->setCasilla(tr->getCasilla() + velocity);
		std::cout << "BOMBA SE IZQDA" << std::endl;
		break;
	case Directions::RIGHT:
		velocity = Vector2D(0.01, 0);
		tr->setCasilla(tr->getCasilla() + velocity);
		std::cout << "BOMBA SE DERECHA" << std::endl;
		break;
	default:
		break;
	}
}

//En este metodo se comprueba si la bomba choca con alguna entidad que puede dañar o con las paredes intraspasables del mapa
void MovementComponentBomb::checkShock() {
	if (!checkIfTileWalkable(tr->getCasilla() + velocity))
		velocity = Vector2D(0, 0);
	//else if()//
	else
		moveBomb(); //Movemos la bomba si no choca con nada
}

void MovementComponentBomb::update() {
	if (isLaunched) { //Aqui habria que detectar el input del player -> o llamar a un metodo que cambie este booleano
		direction = moveFrog->getDirection(); //Obtenemos direccion a la que mira la rana
		isLaunched = false;
		animator->playAnimation("BOMB_IDLE");
	}
	checkShock();
}


