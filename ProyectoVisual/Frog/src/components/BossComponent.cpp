#include "BossComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../scenes/RoomScene.h"


BossComponent::BossComponent() : currState(MOVE), shadowTimer(0), postAttackTimer(2), //
							aviso(&sdlutils().images().at("aviso")) //
{
	texturasCubiertos = new Texture*[MAX_CUBIERTOS];
	texturasCubiertos[0] = &sdlutils().images().at("cuchara"); //Sprite cuchara
	texturasCubiertos[1] = &sdlutils().images().at("cuchilloCarnicero");//Sprite cuchillo carnicero
	texturasCubiertos[2] = &sdlutils().images().at("cuchillo"); //Sprite cuchillo 
	texturasCubiertos[3] = &sdlutils().images().at("tenedor"); //Sprite tenedor
}

BossComponent::~BossComponent()
{
}

void BossComponent::initComponent()
{
	tr = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
	render = ent->getRenderComponent();
	mov = static_cast<MovementComponentFrancois*>(ent->getComponent(MOVEMENT_COMPONENT));
	coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));
	coll->GetTransformCollider()->AddCall([this](Entity* e, Collider c) {attack(e, c); }); //A�adimos callback
	createCutlery(); //Creamos cubiertos
}

void BossComponent::update()
{
	moveCutlery();
}

void BossComponent::generateCutlery()
{
	int rand = sdlutils().rand().nextInt(1 + contDishes, 5 + contDishes); //Cuantos cubiertos tendra el ataque
	for (int i = 0; i < rand; i++) {
		int c = sdlutils().rand().nextInt(CUCHARA, TENEDOR + 1); //Se decide que cubierto se añade a la pool
	}

}

void BossComponent::cleanPool()
{
	for (auto cubierto : poolCubiertos) {
		if (cubierto.second) {
			if (isOutOfScreen(Vector2D(0, cubierto.first->tr_->GetOnDisplayPosition().y)))
				cubierto.second = false;
		}
	}
}

void BossComponent::attack(Entity* e, Collider c)
{
	if (e->getName() == FROG_ENTITY) {
		std::cout << "RANANANANANAN";
	}
	generateCutlery();
}

void BossComponent::createCutlery()
{
	/* L�gica de crear los cubiertos.
		Usar randoms para la aparicion de cada uno, otro para decidir si se crea cuchillo o tenedor, otro para 
		la fila en la que spawnea, y otro para la velocidad que tendr�. */
	Cubierto aux;
	Cubierto* c = &aux;
	for (int i = 0; i < MAX_CUBIERTOS; i++) {
		cubiertos.push_back(c);
		cubiertos[i]->tipo_ = (tipoCubierto)i; //Asignamos id con el tipo de cubierto
		cubiertos[i]->ent_ = new Entity(ent->getScene()); //Creamos entidad cubierto
		cubiertos[i]->tr_ = new TransformComponent(Vector2D(i , i), 80, 160); //Añadimos transform al cubierto
		cubiertos[i]->ent_->addComponent(TRANSFORM_COMPONENT, cubiertos[i]->tr_);
		cubiertos[i]->coll_ = new ColliderComponent(cubiertos[i]->tr_);
		cubiertos[i]->ent_->addComponent(COLLIDER_COMPONENT, cubiertos[i]->coll_);
		cubiertos[i]->render_ = new RenderComponent(texturasCubiertos[i]); //Añadimos la textura pertinente al render
		cubiertos[i]->ent_->addRenderComponent(cubiertos[i]->render_);
		ent->getScene()->AddEntity(cubiertos[i]->ent_); //Añadimos a la lista de entidades
		cubiertos[i]->speed_ = Vector2D(0, -0.1); //Setteamos su velocidad
	}
}

void BossComponent::moveCutlery()
{
	//L�gica para mover los cubiertos que est�n activos en la pool de cubiertos
	for (auto cubierto : poolCubiertos) {
		if (cubierto.second) {
			cubierto.first->tr_->setOffset(cubierto.first->tr_->getOffset() + cubierto.first->speed_);
			cubierto.first->tr_->setCasilla(cubierto.first->speed_ + cubierto.first->tr_->getCasilla());
			cubierto.first->tr_->setOffset({ -cubierto.first->tr_->getCasilla().getX() / 2,
				-cubierto.first->tr_->getCasilla().getY() / 2 });
		}
	}
		
}

void BossComponent::onCutleryCollision(Entity* e, Collider c)
{
	//L�gica de colision con otras entidades de la sala
	if (e->getName() == FROG_ENTITY) {
		//Llamar a callback que reste vida a Flonk
	}
}

bool BossComponent::isOutOfScreen(Vector2D pos) const
{
	//L�gica para obtener la posicion del cubierto y ver si est� fuera de la pantalla
	return pos.getY() >= sdlutils().height();
}



