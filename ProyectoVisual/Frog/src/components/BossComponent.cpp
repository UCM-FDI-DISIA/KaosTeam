#include "BossComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../scenes/RoomScene.h"
#include "LifeComponent.h"
#include <cstdlib>
#include <ctime>

BossComponent::BossComponent() : currState(MOVE), attackStartTime(0), isAttacking(false), //
							postAttackTimer(2), addToList(false), //
							aviso(&sdlutils().images().at("aviso")) //
{
	texturasCubiertos = new Texture*[MAX_CUBIERTOS];
	texturasCubiertos[0] = &sdlutils().images().at("cuchara"); //Sprite cuchara
	texturasCubiertos[1] = &sdlutils().images().at("cuchilloCarnicero");//Sprite cuchillo carnicero
	texturasCubiertos[2] = &sdlutils().images().at("cuchillo"); //Sprite cuchillo 
	texturasCubiertos[3] = &sdlutils().images().at("tenedor"); //Sprite tenedor

	//Semilla para numeros aleatorios
	std::srand(std::time(0));
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
	int numCutlery = sdlutils().rand().nextInt(1 + contDishes, 5 + contDishes); //Cuantos cubiertos tendra el ataque
	for (int i = 0; i < numCutlery; i++) {
		//int c = sdlutils().rand().nextInt(CUCHARA, TENEDOR + 1); //Se decide que cubierto se añade a la pool
		int c = rand() % (TENEDOR + 1); //Decide el cubierto a meter en la pool
		//int x = sdlutils().rand().nextInt(tr->getCasilla().getX(), 
			//tr->getWidth() / ent->getScene()->getMapReader()->getTileSize() + 1); //Definde x random donde ira el cubierto
		int x = rand() % ((int)tr->getWidth() / TILE_SIZE + 1) + tr->getCasilla().getX(); //Definde x random donde ira el cubierto

		cubiertos[c]->tr_->setCasilla(Vector2D(x, -1)); //Ponemos el cubierto una casilla fuera de la pantalla
		cubiertos[c]->tr_->setOffset(Vector2D(-ent->getScene()->getMapReader()->getTileSize() / 2,
			-ent->getScene()->getMapReader()->getTileSize() / 2));

		///Colocamos el aviso en la columna donde posteriormente aparecera un cubierto
		cubiertos[c]->dest_.x = (int)cubiertos[c]->tr_->getWidth();
		cubiertos[c]->dest_.y = (int)cubiertos[c]->tr_->getHeight();
		cubiertos[c]->dest_.w = cubiertos[c]->dest_.h = ent->getScene()->getMapReader()->getTileSize();

		poolCubiertos.emplace_back(std::pair<Cubierto*, bool>(cubiertos[c], true));
		addToList = true;
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
	if (e->getName() == FROG_ENTITY && !isAttacking) {
		isAttacking = true;
		generateCutlery(); //Añadimos los cubiertos
		attackStartTime = sdlutils().currRealTime();
	}
}

void BossComponent::addCutlery()
{
	for (int i = 0; i < poolCubiertos.size(); i++)
		ent->getScene()->AddEntity(poolCubiertos[i].first->ent_);
	addToList = false; //Yaetan creados, no hay nada que añadir
}

void BossComponent::createCutlery()
{
	/* L�gica de crear los cubiertos.
		Usar randoms para la aparicion de cada uno, otro para decidir si se crea cuchillo o tenedor, otro para 
		la fila en la que spawnea, y otro para la velocidad que tendr�. */

	cubiertos.reserve(MAX_CUBIERTOS);
	for (int i = 0; i < MAX_CUBIERTOS; i++) {
		Cubierto* c = new Cubierto;
		c->tipo_ = (tipoCubierto)i; //Asignamos id con el tipo de cubierto
		c->speed_ = Vector2D(0, 0.1); //Setteamos su velocidad
		if (i != 0) c->spawnTime_ = sdlutils().rand().nextInt(0, 3) + cubiertos[i - 1]->spawnTime_;
		else c->spawnTime_ = sdlutils().rand().nextInt(0, 2);

		c->ent_ = new Entity(ent->getScene(), CUTLERY_ENTITY); //Creamos entidad cubierto
		c->tr_ = new TransformComponent(Vector2D(i , i), 80, 160); //Añadimos transform al cubierto
		c->ent_->addComponent(TRANSFORM_COMPONENT, c->tr_);
		c->coll_ = new ColliderComponent(c->tr_);
		c->ent_->addComponent(COLLIDER_COMPONENT, c->coll_);
		c->coll_->GetTransformCollider()->AddCall([this](Entity* e, Collider c) {
			onCutleryCollision(e, c); //Callback si cocha cubierto
			});
		c->render_ = new RenderComponent(texturasCubiertos[i]); //Añadimos la textura pertinente al render
		c->ent_->addRenderComponent(c->render_);

		cubiertos.emplace_back(c); //Metemos el cubierto setteado al vector de cubiertos
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
		static_cast<LifeComponent*>(e->getComponent(LIFE_COMPONENT) )->hit(1);
		//Llamar a callback que reste vida a Flonk
	}
}

bool BossComponent::isOutOfScreen(Vector2D pos) const
{
	//L�gica para obtener la posicion del cubierto y ver si est� fuera de la pantalla
	return pos.getY() >= sdlutils().height();
}



