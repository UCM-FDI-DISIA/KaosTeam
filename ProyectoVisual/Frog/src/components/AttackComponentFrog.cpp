#include "AttackComponentFrog.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "RenderComponentFrog.h"
#include "../utils/Box.h"
#include "ColliderComponent.h"
#include "LifeComponent.h"
#include "../scenes/RoomScene.h"

AttackComponentFrog::AttackComponentFrog() : inputM(InputManager::GetInstance()) {
	distance = 2;
	distanceMoved = 0;
	attackFrameTime = 100;
	lastTimeChanged = 0;
	attackCooldown = 250;
	hitted = false;
	box = new Box();
	elapsedTime = 0;
}

AttackComponentFrog::~AttackComponentFrog() {
	delete box;
}

//comprueba la colision entre la lengua y los diferentes enemigos
void AttackComponentFrog::tongueTouch(Entity* ent, Collider c)
{
	if (!hitted && ent->getName() == COCKROACH_ENTITY && c.getName() == TRANSFORM_COLLIDER) {
		hitted = true;
		elapsedTime = sdlutils().virtualTimer().currTime();
		static_cast<LifeComponent*>(ent->getComponent(LIFE_COMPONENT))->hit(1);  //damage de la rana
		//en el caso de la cucaracha cuando esta muere suelta su cabeza en la escena en la que se encuentren
		if (!static_cast<LifeComponent*>(ent->getComponent(LIFE_COMPONENT))->alive()) {
			scen = static_cast<RoomScene*>(ent->getScene());
			scen->createHeadCockroach(static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT))->getCasilla());
		}
	}
}

void AttackComponentFrog::UpdateBox(Vector2D casilla, int w, int h)
{
	box->setCasilla(casilla);
	box->setWidth(w);
	box->setHeight(h);
}

void AttackComponentFrog::update()
{
	/*
	Hacer aquí set casilla no tiene sentido por q desde el transform no se puede coger la pos de la lengua.
	RenderComponentFrog llama al UpdateBox d esta clase para pasarle la pos d la lengua en cada iteracion con attacking a true
	//box->setCasilla(static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT))->getCasilla());
	*/
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

	//cuando pase el tiempo de espera podra volver a atacar
	if (hitted && sdlutils().virtualTimer().currTime() > elapsedTime + WAIT_ATTACK) {
		hitted = false;
	}
}

void AttackComponentFrog::attack(bool withHook)
{
	lastTimeChanged = DataManager::GetInstance()->getFrameTime();
	state = 1;
	distanceMoved = 0;
	hasHook = withHook;
	static_cast<RenderComponentFrog*>(ent->getRenderComponentFrog())->AttackStart(withHook);
	Collider c = Collider(box, TONGUE_COLLIDER);
	c.AddCall([this](Entity* e, Collider c) {tongueTouch(e, c); });
	static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->AddCollider(c);
}
void AttackComponentFrog::EndAttack()
{
	state = 2;
	hasHook = false;
}

