#include "AttackComponentFrog.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "RenderComponentFrog.h"
#include "../utils/Box.h"
#include "ColliderComponent.h"

AttackComponentFrog::AttackComponentFrog() : inputM(InputManager::GetInstance()) {
	distance = 2;
	distanceMoved = 0;
	attackFrameTime = 100;
	lastTimeChanged = 0;
	attackCooldown = 250;

	box = new Box();

	//std::cout << "Attack Component Frog created " << std::endl;
}

AttackComponentFrog::~AttackComponentFrog() {
	delete box;
}

void AttackComponentFrog::tongueTouch(Entity* ent, Collider c)
{
	//std::cout << "TongueTouch ";	
	switch (ent->getName()) {
	case EntityName::PIEDRAMOV_ENTITY:
		//Destruimos la puerta: ent-> MetodoAlQueLlamar();
		//std::cout << "Empujar piedra" << std::endl;
		break;
	//...Mas casos
	}
	std::cout << ent->getName() << std::endl;
}

void AttackComponentFrog::UpdateBox(Vector2D casilla, int w, int h)
{

	box->setCasilla(casilla);
	box->setWidth(w);
	box->setHeight(h);
	//std::cout << "box update : x: " << box->getCasilla().getX() << " y: " << box->getCasilla().getY() << std::endl;

}

void AttackComponentFrog::update()
{
	//std::cout << " attack box is in casilla.x " << box->getCasilla().getX() << " and casilla.y " << box->getCasilla().getY() << std::endl;
	box->setCasilla(static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT))->getCasilla());
	if (state != 0 && (DataManager::GetInstance()->getFrameTime() - lastTimeChanged) > attackFrameTime) {
		lastTimeChanged = DataManager::GetInstance()->getFrameTime();
		if (state == 1) {
			distanceMoved++;
			if (distanceMoved == distance)
				state++;
			}
		}
		else if (state == 2) {
			distanceMoved--;
			if (distanceMoved < 0) {
				state = 0;
				box->setWidth(0);
				box->setHeight(0);
			}
		}
	}
}

void AttackComponentFrog::attack()
{
	lastTimeChanged = DataManager::GetInstance()->getFrameTime();
	state = 1;
	distanceMoved = 0;
	static_cast<RenderComponentFrog*>(ent->getRenderComponentFrog())->AttackStart();

	//std::cout << std::endl << "colliders BASE: " << static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->GetColliders().size();
	//al llegar al m�ximo de ataque se a�ade su box a la escena para calcular sus colisiones
	Collider c = Collider(box);
	//std::cout << " attack coll box created in casilla.x " << box->getCasilla().getX() << " and casilla.y " << box->getCasilla().getY() << std::endl;
	c.AddCall([this](Entity* e, Collider c) {tongueTouch(e, c); }); //A�adimos callback
	static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->AddCollider(c);
	//std::cout << std::endl << "COLLIDER FOR LENGUA " << static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->GetColliders().size();
	SDL_Rect collRect = box->GetOnDisplayPosition();
	//std::cout << " attack coll box is.x " << collRect.x << " and is.y " << collRect.y << " and is.w " << collRect.w << " and is.h " << collRect.h << std::endl;
}

void AttackComponentFrog::EndAttack()
{
	state = 2;
}

