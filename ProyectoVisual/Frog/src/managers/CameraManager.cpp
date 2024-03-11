#include "CameraManager.h"
//Camera* Camera::cameraInstance = nullptr;

Camera::Camera(Entity* target, MapManager* room) :
	camTarget(target), actualRoom(room) {
	mapCanMove = true;
}
void Camera::update() {

	if (camTargetMovementComp->getMoveCompleted()) {
		switch (camTargetMovementComp->getDirection()) {
		case UP:
			if (mapCanMove) {
				actualRoom->move("down");
				mapCanMove = false;
			}
			break;
		case DOWN:
			if (mapCanMove) {
				actualRoom->move("up");
				mapCanMove = false;
			}
			break;
		case RIGHT:
			if (mapCanMove) {
				actualRoom->move("left");
				mapCanMove = false;
			}
			break;
		case LEFT:
			if (mapCanMove) {
				actualRoom->move("right");
				mapCanMove = false;
			}
			break;
		default:
			break;
		}
	}
	else if (!camTargetMovementComp->getMoveCompleted()) {
		mapCanMove = true;
	}
}