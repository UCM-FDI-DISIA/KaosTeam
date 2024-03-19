#pragma once

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H	

#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
#include "../components/MovementComponentFrog.h"
#include "../utils/Singleton.h"



class Camera: public Singleton<Camera> { 

	friend Singleton<Camera>;
public:

	void setTarget(Entity* target);

	/*inline void setRoom(MapManager* newRoom) {
		actualRoom = newRoom;
	}*/
	void update();
	void setMapCanMove(){mapCanMove = true;}
	Vector2D getCameraMovement() { return cameraPos; }


private:
	//static Camera* cameraInstance;
	Entity* camTarget;
	Vector2D cameraPos = { 0,0 };
	Vector2D lastTargetPosition;
	Camera() {};
	//ns si esta bien
	MovementComponentFrog* camTargetMovementComp;
	//MapManager* actualRoom;
	bool mapCanMove;
};
#endif // !CAMERAMANAGER_H