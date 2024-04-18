#include "../sdlutils/VirtualTimer.h"
#include "MovementComponentBomb.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../scenes/RoomScene.h"

MovementComponentBomb::MovementComponentBomb() : shockEntity(false), direction(NONE) {
}

void MovementComponentBomb::initComponent() {
	//Obtenemos componentes necesarios
	moveFrog = static_cast<MovementComponentFrog*>(ent->getScene()->getPlayer()->getComponent(MOVEMENT_COMPONENT));
	animator = static_cast<AnimationComponent*>(ent->getComponent(ANIMATION_COMPONENT));
	tr = static_cast<TransformComponent*> (ent->getComponent(TRANSFORM_COMPONENT));
	coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));
	rndr = static_cast<RenderComponent*>(ent->getComponent(RENDER_COMPONENT));

	//Inicilaizamos valores que vaa tener en cuanto la bomba se instancie
	direction = moveFrog->getDirection();
	animator->playAnimation("BOMB_IDLE");

	// Aqu� envolvemos la funci�n checkEntityShock en un objeto std::function
	coll->AddCall([this](Entity* e) {checkCollisionsBomb(e); }); //A�adimos callback
}

// Esta funci�n, se llamar� en cada iteracci�n del update para detectar con que entity colisiona y hacer las correspondientes acciones
//(Mi idea era hacer el metodo aqui, sin embargo, no puedo acceder a la entidad contra la que colisiona
// la bomba desde aqu�, asi que no me queda mas remedio que hacerlo en la RoomScene...)
void MovementComponentBomb::checkCollisionsBomb(Entity* ent) {
	switch (ent->getName()) {
	case EntityName::BREAKABLE_DOOR_ENTITY:
		//Destruimos la puerta: ent-> MetodoAlQueLlamar(); 
		std::cout << "PUERTA DESTRUIDA" << std::endl;
		break;
	case EntityName::INTERRUPTOR_ENTITY:
		//Activamos interruptor
		std::cout << "INTERRUPTOR ACTIVADO" << std::endl;
		break;
	case EntityName::SNAKE_ENTITY:
		//Quitariamos vida a la serpiente...
		ent->getScene()->removeEntity(ent);
		//Eliminamos a la bomba
		explodeBomb();
		std::cout << "SERPIENTE DADA CON BOMBA" << std::endl;
		break;
	}
}

//Mueve la bomba en la direccion dada:
void MovementComponentBomb::moveBomb() {
	switch (direction) {
	case Directions::DOWN:
		velocity = Vector2D(0, 0.01);
		tr->setCasilla(tr->getCasilla() + velocity);
		break;
	case Directions::UP:
		velocity = Vector2D(0, -0.01);
		tr->setCasilla(tr->getCasilla() + velocity);
		break;
	case Directions::LEFT:
		velocity = Vector2D(-0.01, 0);
		tr->setCasilla(tr->getCasilla() + velocity);
		break;
	case Directions::RIGHT:
		velocity = Vector2D(0.01, 0);
		tr->setCasilla(tr->getCasilla() + velocity);
		break;
	default:
		break;
	}
}

//En este metodo se comprueba si la bomba choca con alguna entidad que puede da�ar o con las paredes intraspasables del mapa
void MovementComponentBomb::checkShock() {
	if (!checkIfTileWalkable(tr->getCasilla() + velocity) || shockEntity)
		explodeBomb();
	else
		moveBomb(); //Movemos la bomba si no choca con nada
}

//Este metodo se ejecuta en caso de que la bomba choque con algo
//Simplemente har�a la animaci�n de explosi�n y su sonido, y una vez hecho eso, elimina la bomba de la escena de la escena
void MovementComponentBomb::explodeBomb() {
	animator->stopAnimation(); //Paramos animacion actual
	animator->removeAnimations(); //Quitamos animaciones existentes
	rndr->ChangeTexture(explosionText); //cambiamos la textura del objeto (al spriteSheet de la explosion)
	animator->addAnimation("EXPLOSION", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, true));
	animator->playAnimation("EXPLOSION"); //Reproducimos explosi�n

	shockEntity = true;
	velocity = Vector2D(0, 0);

	timerForDelete.reset(); //reseteamos timer
}

void MovementComponentBomb::update() {
	// Si ha pasado un tiempo suficiente desde la explosi�n, eliminamos la entidad
	if (timerForDelete.currTime() >= 2000 && shockEntity) { // explosionDuration es el tiempo en milisegundos
		ent->getScene()->removeEntity(this->ent);
	}
	checkShock();
}


