#include "MovementComponentBomb.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../scenes/RoomScene.h"

MovementComponentBomb::MovementComponentBomb() : shockEntity(false), direction(NONE), explosionTime(2000) {
	timerForDelete.pause(); //pausamos timer de explosión (solo se activa cuando la bomba ha chocado con algo)
}

MovementComponentBomb::~MovementComponentBomb(){
	delete explosionText;
	moveFrog = nullptr;
	animator = nullptr;

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


	//Añadimos funcion de collider a la bomba
	//std::list<Collider> listCol = coll->GetColliders(); //Accedemos a la lista de colliders
	coll->GetColliders().front().AddCall([this](Entity* e) {checkCollisionsBomb(e); }); //Añadimos callback
}

// Esta función, se llamará en cada iteracción del update para detectar con que entity colisiona y hacer las correspondientes acciones
//(Mi idea era hacer el metodo aqui, sin embargo, no puedo acceder a la entidad contra la que colisiona
// la bomba desde aquí, asi que no me queda mas remedio que hacerlo en la RoomScene...)
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

	//...Mas casos
	}
}

//Mueve la bomba en la direccion dada:
void MovementComponentBomb::moveBomb() {
	switch (direction) {
	case Directions::DOWN:
		velocity = Vector2D(0, 0.01);
		//velocity = Vector2D(0, 0);
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

//En este metodo se comprueba si la bomba choca con las paredes intraspasables del mapa
//las colisiones con entidades lo hace checkCollisionsBomb() que es un callback del collider que se llama en cada update de RoomScene
void MovementComponentBomb::checkShock() {
	if (!checkIfTileWalkable(tr->getCasilla() + velocity))
		explodeBomb();
}

//Este metodo se ejecuta en caso de que la bomba choque con algo
//Simplemente haría la animación de explosión y su sonido, y una vez hecho eso, elimina la bomba de la escena despues de un tiempo
void MovementComponentBomb::explodeBomb() {

	animator->stopAnimation(); //Paramos animacion actual
	animator->removeAnimations(); //Quitamos animaciones existentes
	rndr->ChangeTexture(explosionText); //cambiamos la textura del objeto (al spriteSheet de la explosion)
	animator->addAnimation("EXPLOSION", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, true));
	animator->playAnimation("EXPLOSION"); //Reproducimos explosión

	shockEntity = true;
	velocity = Vector2D(0, 0);

	timerForDelete.resume(); //Activamos timer para eliminar la bomba despues de un cierto tiempo
}

void MovementComponentBomb::update() {
	// Si ha pasado un tiempo suficiente desde la explosión, eliminamos la entidad
	if (timerForDelete.currTime() >= explosionTime) {
		ent->getScene()->removeEntity(this->ent);
	}
	
	checkShock();
	
	//Si no ha chocado con nada, movemos la bomba
	if (!shockEntity) moveBomb();
}


