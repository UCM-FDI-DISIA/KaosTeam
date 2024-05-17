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
	void update();
	Vector2D getCameraMovement() { return cameraPos;} 

	//para hacer el movimiento fluido
	Vector2D GetAdditionalOffset();
	virtual ~Camera();

private:
	//static Camera* cameraInstance;
	Entity* camTarget;
	Vector2D cameraPos = { 0,0 };
	int limitX, limitY, tilesToStartMovingX, tilesToStartMovingY; 
	int tileSize;
	Vector2D screenSize; //IMPORTANTE en casillas
	Vector2D targetPosition;
	Vector2D additionalOffset;
	Directions direction;
	Camera() {};
	
	TransformComponent* targetTransform;
	
};
#endif // !CAMERAMANAGER_H