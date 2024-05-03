#include "BossComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../scenes/RoomScene.h"
#include "LifeComponent.h"

BossComponent::BossComponent() : currState(MOVE), attackStartTime(0), postAttackTimer(2), //
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
	rnd = ent->getRenderComponent();
	mov = static_cast<MovementComponentFrancois*>(ent->getComponent(MOVEMENT_COMPONENT));
	coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));
	coll->GetTransformCollider()->AddCall([this](Entity* e, Collider c) { 
		attack(e, c); 
		}); //A�adimos callback
	createCutlery(); //Creamos cubiertos
}

void BossComponent::update()
{
	if(!poolCubiertos.empty())
		moveCutlery();
}

void BossComponent::render()
{
	for (int i = 0; i < poolCubiertos.size(); i++) {
		//Pintar la señal de aviso
		if (attackStartTime + poolCubiertos[i].first->spawnTime_ >= sdlutils().currRealTime())
			aviso->render(poolCubiertos[i].first->dest_);
	}
}

void BossComponent::generateCutlery()
{
	//int numCutlery = sdlutils().rand().nextInt(1 + contDishes, 5 + contDishes); //Cuantos cubiertos tendra el ataque
	for (int i = 0; i < /*numCutlery*/1; i++) {
		int c = sdlutils().rand().nextInt(CUCHARA, TENEDOR + 1); //Se decide que cubierto se añade a la pool
		int x = sdlutils().rand().nextInt(tr->getCasilla().getX(), 
			tr->getWidth() / ent->getScene()->getMapReader()->getTileSize() + 1); //Definde x random donde ira el cubierto
		pair<Cubierto*, bool> cubierto(cubiertos[c], true);
		
		cubierto.first->tr_->setCasilla(Vector2D(x, -1)); //Ponemos el cubierto una casilla fuera de la pantalla
		cubierto.first->tr_->setOffset(Vector2D(-ent->getScene()->getMapReader()->getTileSize() / 2,
			-ent->getScene()->getMapReader()->getTileSize() / 2));

		//Colocamos el aviso en la columna donde posteriormente aparecera un cubierto
		cubierto.first->dest_.x = (int)cubierto.first->tr_->getWidth();
		cubierto.first->dest_.y = (int)cubierto.first->tr_->getHeight();
		cubierto.first->dest_.w = cubierto.first->dest_.h = ent->getScene()->getMapReader()->getTileSize();

		ent->getScene()->AddEntity(cubierto.first->ent_); //Añadimos cubierto a la lista de entidades para usarlo
		poolCubiertos.push_back(cubierto);
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
		//std::cout << "RANANANANANAN"; //Para comprobar si se llama al callback
		generateCutlery();
		attackStartTime = sdlutils().currRealTime();
	}
}

void BossComponent::createCutlery()
{
	/* L�gica de crear los cubiertos.
		Usar randoms para la aparicion de cada uno, otro para decidir si se crea cuchillo o tenedor, otro para 
		la fila en la que spawnea, y otro para la velocidad que tendr�. */
	Cubierto aux;
	Cubierto* c = &aux;
	for (int i = 0; i < MAX_CUBIERTOS; i++) {
		c->tipo_ = (tipoCubierto)i; //Asignamos id con el tipo de cubierto
		c->speed_ = Vector2D(0, 0.1); //Setteamos su velocidad
		if (i != 0) c->spawnTime_ = sdlutils().rand().nextInt(0, 3) + cubiertos[i - 1]->spawnTime_;
		else c->spawnTime_ = sdlutils().rand().nextInt(0, 2);

		c->ent_ = new Entity(ent->getScene()); //Creamos entidad cubierto
		c->tr_ = new TransformComponent(Vector2D(i , i), 80, 160); //Añadimos transform al cubierto
		c->ent_->addComponent(TRANSFORM_COMPONENT, c->tr_);
		c->coll_ = new ColliderComponent(c->tr_);
		c->ent_->addComponent(COLLIDER_COMPONENT, c->coll_);
		c->coll_->GetTransformCollider()->AddCall([this](Entity* e, Collider c) {
			onCutleryCollision(e, c); 
			});
		c->render_ = new RenderComponent(texturasCubiertos[i]); //Añadimos la textura pertinente al render
		c->ent_->addRenderComponent(c->render_);
		//ent->getScene()->AddEntity(cubiertos[i]->ent_); //Añadimos a la lista de entidades

		cubiertos.push_back(c); //Metemos el cubierto setteado al vector de cubiertos
	}
}

void BossComponent::moveCutlery()
{
	//L�gica para mover los cubiertos que est�n activos en la pool de cubiertos
	for (pair cubierto : poolCubiertos) {
		if (cubierto.second && attackStartTime + cubierto.first->spawnTime_ >= sdlutils().currRealTime()) {
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
		std::cout<<static_cast<LifeComponent*>(e->getComponent(LIFE_COMPONENT))->GetActual();
		//Llamar a callback que reste vida a Flonk
	}
}

bool BossComponent::isOutOfScreen(Vector2D pos) const
{
	//L�gica para obtener la posicion del cubierto y ver si est� fuera de la pantalla
	return pos.getY() >= sdlutils().height();
}



