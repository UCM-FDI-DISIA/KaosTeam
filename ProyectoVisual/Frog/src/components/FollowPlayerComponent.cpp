#include "FollowPlayerComponent.h"
#include "../scenes/RoomScene.h"
#include "../ecs/Entity.h"

FollowPlayerComponent::FollowPlayerComponent(Vector2D pos)
	: MovementComponent(), vel(0, 0), lastTimeMoved(SDL_GetTicks())
{}

FollowPlayerComponent::~FollowPlayerComponent() {

}

void FollowPlayerComponent::update() {
	if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime) {
		TransformComponent* transform = ent->getComponent<TransformComponent>(TRANSFORM_COMPONENT);
		RoomScene* sc = ent->getScene();// coje la pocision del player
		Entity* pl = sc->getPlayer();
		TransformComponent* pmt = pl->getComponent<TransformComponent>(TRANSFORM_COMPONENT);
		Vector2D playerPos = pmt->getCasilla();
		Vector2D aux = playerPos - transform->getCasilla();
		//sacar X e Y y comparar
		float ax = aux.getX();
		float ay = aux.getY();
		if (ax < 0) {
			ax *= -1;
		}
		if (ay < 0) {
			ay *= -1;
		}
		if (ax == 0 && ay == 0) {
			vel.set(0, 0);
		}
		else if (ax == 0) {
			if (aux.getY() < 0) {
				vel.set(0, -1);
			}
			else {
				vel.set(0, 1);
			}
		}
		else if (ay == 0) {
			if (aux.getX() < 0) {
				vel.set(-1, 0);
			}
			else {
				vel.set(1, 0);
			}
		}
		else if (ax < ay) {
			if (aux.getX() < 0) {
				vel.set(-1, 0);
			}
			else {
				vel.set(1, 0);
			}
		}
		else {
			if (aux.getY() < 0) {
				vel.set(0, -1);
			}
			else {
				vel.set(0, 1);
			}
		}
		//aplicar movimiento
		transform->setCasilla(transform->getCasilla() + vel);

		lastTimeMoved = SDL_GetTicks();
	}
	
}
