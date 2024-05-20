#include "MovementComponentBomb.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../scenes/RoomScene.h"



MovementComponentBomb::MovementComponentBomb() : shockEntity(false), direction(NONE), explosionTime(2000) {
	timerForDelete.pause(); //pausamos timer de explosi�n (solo se activa cuando la bomba ha chocado con algo)
}

MovementComponentBomb::~MovementComponentBomb(){
	delete explosionText;
	moveFrog = nullptr;

}

void MovementComponentBomb::initComponent() {
	//Obtenemos componentes necesarios
	moveFrog = static_cast<MovementComponentFrog*>(ent->getScene()->getPlayer()->getComponent(MOVEMENT_COMPONENT));
	AnimationComponent* animator = static_cast<AnimationComponent*>(ent->getComponent(ANIMATION_COMPONENT));
	tr = static_cast<TransformComponent*> (ent->getComponent(TRANSFORM_COMPONENT));
	coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));
	//rndr = static_cast<RenderComponent*>(ent->getComponent(RENDER_COMPONENT));


	//Inicilaizamos valores que vaa tener en cuanto la bomba se instancie
	direction = moveFrog->getDirection();
	animator->playAnimation("BOMB_IDLE");


	//A�adimos funcion de collider a la bomba
	//std::list<Collider> listCol = coll->GetColliders(); //Accedemos a la lista de colliders
	coll->GetTransformCollider()->AddCall([this](Entity* e, Collider c) {checkCollisionsBomb(e, c); }); //Anadimos callback
}

// Esta funci�n, se llamar� en cada iteracci�n del update para detectar con que entity colisiona y hacer las correspondientes acciones
//(Mi idea era hacer el metodo aqui, sin embargo, no puedo acceder a la entidad contra la que colisiona
// la bomba desde aqu�, asi que no me queda mas remedio que hacerlo en la RoomScene...)
void MovementComponentBomb::checkCollisionsBomb(Entity* ent, Collider c) {
	if (!shockEntity) { //Comprobamos que ya 
		LifeComponent* lifeEntity = static_cast<LifeComponent*>(ent->getComponent(LIFE_COMPONENT));
		if (lifeEntity != nullptr) {
			//Da�ar a la entidad en uno
			lifeEntity->hit(1); //bajamos vida de la entidad con la que choca
			explodeBomb(); //En ambos casos la bomba explota
		}
		else if (ent->getName() == EntityName::EXPLOITABLE_ENTITY) {
			//Destruyes el objeto explotable
			ExploitableComponent* exp = static_cast<ExploitableComponent*>(ent->getComponent(EXPLOITABLE_COMPONENT));
			//Metodo a llamar
			exp->exploitEntity();
			explodeBomb();
		}
		
	}
}


//Mueve la bomba en la direccion dada:
void MovementComponentBomb::moveBomb() {
	switch (direction) {
	case Directions::DOWN:
		velocity = Vector2D(0, 0.1);
		tr->setCasilla(tr->getCasilla() + velocity);
		break;
	case Directions::UP:
		velocity = Vector2D(0, -0.1);
		tr->setCasilla(tr->getCasilla() + velocity);
		break;
	case Directions::LEFT:
		velocity = Vector2D(-0.1, 0);
		tr->setCasilla(tr->getCasilla() + velocity);
		break;
	case Directions::RIGHT:
		velocity = Vector2D(0.1, 0);
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
//Simplemente har�a la animaci�n de explosi�n y su sonido, y una vez hecho eso, elimina la bomba de la escena despues de un tiempo
void MovementComponentBomb::explodeBomb() {
	setCanMove(false);
	AnimationComponent* animator = static_cast<AnimationComponent*>(ent->getComponent(ANIMATION_COMPONENT));
	RenderComponent* rndr = ent->getRenderComponent();

	animator->stopAnimation(); //Paramos animacion actual
	animator->removeAnimations(); //Quitamos animaciones existentes
	rndr->ChangeTexture(explosionText); //cambiamos la textura del objeto (al spriteSheet de la explosion)
	animator->addAnimation("EXPLOSION", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, false, true));
	animator->playAnimation("EXPLOSION"); //Reproducimos explosi�n
	sdlutils().soundEffects().at("Explosion").play();

	shockEntity = true;
	velocity = Vector2D(0, 0);

	timerForDelete.resume(); //Activamos timer para eliminar la bomba despues de un cierto tiempo
}

void MovementComponentBomb::update() {
	// Si ha pasado un tiempo suficiente desde la explosi�n, eliminamos la entidad
	if (timerForDelete.currTime() >= explosionTime) {
		ent->getScene()->removeEntity(this->ent);
	}
	
	checkShock();
	
	//Si no ha chocado con nada, movemos la bomba
	if (!shockEntity) moveBomb();
}


