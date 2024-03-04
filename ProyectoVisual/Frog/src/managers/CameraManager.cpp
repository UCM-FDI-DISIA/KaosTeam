#include "CameraManager.h"
#include "../game/Game.h"
Camera* Camera::cameraInstance = nullptr;

Camera::Camera(Entity* target, MapManager* room) :
	camTarget(target), actualRoom(room) {
	offsetX = (actualRoom->getTileSize() - WIDTH_CAM); //
	offsetY = (actualRoom->getTileSize() - HEIGHT_CAM); //
	limitTop = offsetY;
	limitBotton = HEIGHT_CAM - offsetY;
	limitRight = WIDTH_CAM - offsetX;
	limitLeft = offsetX;
	speed = camTarget->getSpeed();
}
void Camera::update() {
	if (camTarget->getMove()) {

		//si player supera el limite de la izquieda
		if ((camTarget->getX() - offsetX < limitLeft) && actualRoom->getX() > 0 && camTarget->getDirectionY() == 0) {

			if (camTarget->getDirectionX() == -1) actualRoom->moveRight(speed, 0);
			else actualRoom->moveLeft(speed, -offsetX);

		}
		//si player supera el limite de la derecha
		else if ((camTarget->getX() + offsetX > limitRight) && camTarget->getDirectionY() == 0) {

			if (camTarget->getDirectionX() == -1) actualRoom->moveRight(speed, 0);
			else actualRoom->moveLeft(speed, -offsetX);
		}
		//si player supera el limite de arriba
		else if ((camTarget->getY() < limitTop) && actualRoom->getY() > 0 && camTarget->getDirectionX() == 0) {

			if (camTarget->getDirectionY() == -1) actualRoom->moveDown(speed, 0);
			else actualRoom->moveUp(speed, -offsetY);
		}
		//si player supera el limite de abajo 
		else if ((camTarget->getY() > limitBotton) && actualRoom->getY() < actualRoom->getTileSize() && camTarget->getDirectionX() == 0) {

			if (camTarget->getDirectionY() == -1) actualRoom->moveDown(speed, 0);
			else actualRoom->moveUp(speed, -offsetY);
		}
	}
	
}

