#include "FollowPlayerComponent.h"
#include "../scenes/RoomScene.h"
#include "../ecs/Entity.h"

FollowPlayerComponent::FollowPlayerComponent(Vector2D pos)
	:MovementComponent(pos), vel(0, 0), lastTimeMoved(SDL_GetTicks())
{}

FollowPlayerComponent::~FollowPlayerComponent() {

}

void FollowPlayerComponent::FollowPlayer(float x, float y) {
	//Vector2D playerPos = scene->GetPlayerPos(); // coje la pocision del player
	Vector2D playerPos(x, y);
	Vector2D aux = playerPos - posCasilla;
	//sacar X e Y y comparar
	float ax = aux.getX();
	float ay = aux.getY();
	if (ax < 0) {
		ax *= -1;
	}
	if (ay < 0) {
		ay *= -1;
	}
	if (ax == 0 || ay == 0) {
		if (ax == 0) {
			if (aux.getY() < 0) {
				vel.set(0, -1);
			}
			else {
				vel.set(0, 1);
			}
		}
		else {
			if (aux.getX() < 0) {
				vel.set(-1, 0);
			}
			else {
				vel.set(1, 0);
			}
		}
	}
	else if (ax < ay) {
	    if(aux.getX() < 0) {
		    vel.set(-1,0);
		}
		else {
		    vel.set(1,0);
		}
	}
	else {
	    if(aux.getY() < 0) {
		    vel.set(0,-1);
		}
		else {
		    vel.set(0,1);
		}
	}
	//aplicar movimiento
	std::cout << vel << std::endl;
}

void FollowPlayerComponent::update() {
	if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime) {
		RoomScene* sc = ent->getScene();// coje la pocision del player
		Entity* pl = sc->getPlayer();
		MovementComponent* pmc = static_cast<MovementComponent*>(pl->getComponent(MOVEMENT_COMPONENT));
		Vector2D playerPos = pmc->getPosition();
		Vector2D aux = playerPos - posCasilla;
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
		posCasilla = posCasilla + vel;

		lastTimeMoved = SDL_GetTicks();
	}
	
}
