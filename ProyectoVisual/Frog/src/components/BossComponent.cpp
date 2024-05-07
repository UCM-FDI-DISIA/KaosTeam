#include "BossComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../scenes/RoomScene.h"
#include "LifeComponent.h"
#include <cstdlib>
#include <ctime>

BossComponent::BossComponent() : currState(MOVE), attackStartTime(0), isAttacking(false), numCubiertos(0), //
							postAttackTimer(0), addToList(false), isDetected(false), //
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
	if (!isAttacking && !isDetectingFlonk()) {
		postAttackTimer++;
		isDetected = false;
	}
	else {
		moveCutlery(); //Si hay cubiertos, se mueven los cubiertos los que haya
		cleanPool();
		attackStartTime++;
	}
}

void BossComponent::render()
{
	for (int i = 0; i < poolCubiertos.size(); i++) {
		//Pintar la señal de aviso
		if (attackStartTime <= poolCubiertos[i].first->spawnTime_)
			aviso->render(poolCubiertos[i].first->dest_);
	}
}

void BossComponent::generateCutlery()
{
	int numCutlery = rand() % 5 + MINIMUM_CUTLERY_PER_ATTACK + contDishes; //Cuantos cubiertos tendra el ataque
	for (int i = 0; i < numCutlery; i++) {
		int c = rand() % (TENEDOR + 1); //Decide el cubierto a meter en la pool
		int x = rand() % ((int)tr->getWidth() / TILE_SIZE + 1) + tr->getCasilla().getX(); //Definde x random donde ira el cubierto

		cubiertos[c]->tr_->setCasilla(Vector2D(x, -1)); //Ponemos el cubierto una casilla fuera de la pantalla
		cubiertos[c]->tr_->setOffset(Vector2D(-ent->getScene()->getMapReader()->getTileSize() / 2,
			-ent->getScene()->getMapReader()->getTileSize() / 2));

		///Colocamos el aviso en la columna donde posteriormente aparecera un cubierto
		cubiertos[c]->dest_.x = (int)cubiertos[c]->tr_->getCasilla().getX() * TILE_SIZE;
		cubiertos[c]->dest_.y = 0;
		cubiertos[c]->dest_.w = cubiertos[c]->dest_.h = ent->getScene()->getMapReader()->getTileSize();

		poolCubiertos.emplace_back(std::pair<Cubierto*, bool>(cubiertos[c], true));
		numCubiertos++;
		addToList = true;
	}
}

void BossComponent::cleanPool()
{
	for (auto cubierto : poolCubiertos) {
		if (isOutOfScreen(cubierto.first->tr_->getCasilla().getY() * TILE_SIZE) && cubierto.second) {
			cubierto.second = false;
			numCubiertos--;
			if (numCubiertos == 0) {
				isAttacking = false;
			}
		}
	}
}

void BossComponent::attack(Entity* e, Collider c)
{
	isDetected = true;
	if (e->getName() == FROG_ENTITY && !isAttacking && postAttackTimer >= TIME_AFTER_ATTACK) {
		isAttacking = true;
		postAttackTimer = 0;
		generateCutlery(); //Añadimos los cubiertos
		attackStartTime = 0;
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
		if (i != 0) c->spawnTime_ = rand() % 100 + cubiertos[i - 1]->spawnTime_;
		//c->spawnTime_ = sdlutils().rand().nextInt(0, 3) + cubiertos[i - 1]->spawnTime_;
		else c->spawnTime_ = rand() % 8 + 100;
		//c->spawnTime_ = sdlutils().rand().nextInt(0, 2);

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
		if (cubierto.second && attackStartTime >= cubierto.first->spawnTime_) {
			//cubierto.first->tr_->setOffset(cubierto.first->tr_->getOffset() + cubierto.first->speed_);
			cubierto.first->tr_->setCasilla(cubierto.first->speed_ + cubierto.first->tr_->getCasilla());
			//cubierto.first->tr_->setOffset({ -cubierto.first->tr_->getCasilla().getX() / 2,
				//-cubierto.first->tr_->getCasilla().getY() / 2 });
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

bool BossComponent::isOutOfScreen(float y) const
{
	//L�gica para obtener la posicion del cubierto y ver si est� fuera de la pantalla
	return y >= sdlutils().height();
}

bool BossComponent::isOnTheShadow(const float & x) const
{
	return tr->getCasilla().getX() < x
		&& tr->getCasilla().getX() + tr->getWidth() / TILE_SIZE > x;
}

bool BossComponent::isDetectingFlonk() const
{
	return isOnTheShadow(static_cast<TransformComponent*>(ent->getScene()->getPlayer()->getComponent(TRANSFORM_COMPONENT))->getCasilla().getX());
}


