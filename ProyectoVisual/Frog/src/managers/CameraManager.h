#pragma once

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H	

#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
#include "MapManager.h"
#include <SDL.h>
//#include "../game/Game.h"
static constexpr int WIDTH_CAM = 800;
static constexpr int HEIGHT_CAM = 600;
class Game;
class Camera { //en un futuro miro si puede heredar te component
public:
	inline static Camera* getInstance(Entity* target, MapManager* room)
	{ return cameraInstance = (cameraInstance != nullptr) ? cameraInstance : new Camera(target,room); }

	//inline Vector2D getCameraPosition() { return camPos; }
	inline void setTarget(Entity* target) { camTarget = target; }
	inline void setRoom(MapManager* newRoom) {
		actualRoom = newRoom;
	}
	void update();

private:
	static Camera* cameraInstance;
	Game* game;
	Entity* camTarget;
	MapManager* actualRoom;
	int offsetX;
	int offsetY;
	int limitTop;
	int limitBotton;
	int limitRight;
	int limitLeft;
	int speed;
	Camera(Entity* target, MapManager* room );
};
#endif // !CAMERAMANAGER_H