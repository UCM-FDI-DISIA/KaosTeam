#include "CameraManager.h"
//Camera* Camera::cameraInstance = nullptr;

Camera::Camera(Entity* target, MapManager* room) :
	camTarget(target), actualRoom(room) {
}
void Camera::update() {
	
	if (camTarget->getMove()) {

		if (camTarget->getDirectionY() == 0) {
			if (camTarget->getDirectionX() == -1) actualRoom->move("right");
			else actualRoom->move("left");
		}
		else if (camTarget->getDirectionX() == 0) {
			if (camTarget->getDirectionY() == -1) actualRoom->move("down");
			else actualRoom->move("up");
		}
		////si player supera el limite de la izquieda
		//if ((camTarget->getX() - offsetX < limitLeft) /*&& actualRoom->getX() > 0*/ && camTarget->getDirectionY() == 0) {
		//	if (camTarget->getDirectionX() == -1) actualRoom->moveRight(speed, 0);
		//	else actualRoom->moveLeft(speed, -offsetX);
		//}
		////si player supera el limite de la derecha
		//else if ((camTarget->getX() + offsetX > limitRight) && camTarget->getDirectionY() == 0) {
		//	if (camTarget->getDirectionX() == -1) actualRoom->moveRight(speed, 0);
		//	else actualRoom->moveLeft(speed, -offsetX);
		//}
		////si player supera el limite de arriba
		//else if ((camTarget->getY() < limitTop) /*&& actualRoom->getY() > 0*/ && camTarget->getDirectionX() == 0) {
		//	if (camTarget->getDirectionY() == -1) actualRoom->moveDown(speed, 0);
		//	else actualRoom->moveUp(speed, -offsetY);
		//}
		////si player supera el limite de abajo 
		//else if ((camTarget->getY() > limitBotton) && /*actualRoom->getY() < actualRoom->getTileSize() &&*/ camTarget->getDirectionX() == 0) {
		//	if (camTarget->getDirectionY() == -1) actualRoom->moveDown(speed, 0);
		//	else actualRoom->moveUp(speed, -offsetY);
		//}
	}
}
//void Camera::handleEvents(const SDL_Event& event) { //maneja los eventos del teclado que realizan el movimiento lateral y disparo 
//	if (event.type == SDL_KEYDOWN) {
//		switch (event.key.keysym.sym) {
//		case SDLK_d:
//			actualRoom->move("left");
//			break;
//		case SDLK_a:
//			actualRoom->move("right");
//			break;
//		case SDLK_w:
//			actualRoom->move("down");
//			break;
//		case SDLK_s:
//			actualRoom->move("up");
//			break;
//		}
//	}
//}

