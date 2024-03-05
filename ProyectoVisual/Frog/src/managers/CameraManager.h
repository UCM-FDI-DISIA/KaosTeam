#pragma once

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H	

#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
#include "MapManager.h"
#include <SDL.h>
class Camera { //en un futuro miro si puede heredar de component
public:
	Camera(Entity* target, MapManager* room);
	/*inline static Camera* getInstance(Entity* target, MapManager* room)
	{ return cameraInstance = (cameraInstance != nullptr) ? cameraInstance : new Camera(target,room); }*/

	inline void setTarget(Entity* target) { camTarget = target; }
	inline void setRoom(MapManager* newRoom) {
		actualRoom = newRoom;
	}
	void update();
	//void handleEvents(const SDL_Event& event);
private:
	static Camera* cameraInstance;
	Entity* camTarget;
	MapManager* actualRoom;
};
#endif // !CAMERAMANAGER_H