#include "FollowPlayerComponent.h"

FollowPlayerComponent::FollowPlayerComponent(float x, float y)
	:MovementComponent(x,y), vel(0, 0)
{}

FollowPlayerComponent::~FollowPlayerComponent() {

}

void FollowPlayerComponent::FollowPlayer(float x, float y) {
	//Vector2D playerPos = scene->GetPlayerPos(); // coje la pocision del player
	Vector2D playerPos(x, y);
	Vector2D aux = playerPos - pos;
	//sacar X e Y y comparar
	float ax = aux.getX();
	float ay = aux.getY();
	if (ax < 0) {
		ax *= -1;
	}
	if (ay < 0) {
		ay *= -1;
	}
	if (ax < ay) {
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
	std::cout << vel << std::endl;
}
