#include "CameraManager.h"
#include "../scenes/RoomScene.h"

void Camera::setTarget(Entity* target)
{
	camTarget = target;
	camTargetMovementComp = dynamic_cast<MovementComponentFrog*>(camTarget->getComponent(MOVEMENT_COMPONENT));
	lastTargetPosition = camTargetMovementComp->getPosition();
	limitX = target->getScene()->getMapReader()->getCols();
	limitY = target->getScene()->getMapReader()->getRows();
}
void Camera::update() {

	Vector2D actualTargetPos = camTargetMovementComp->getPosition();
	if (lastTargetPosition.getX() != actualTargetPos.getX() || lastTargetPosition.getY() != actualTargetPos.getY()) {
		
		if ((actualTargetPos.getX() > tilesToStartMoving || cameraPos.getX() >0) &&	//si te has movido lo suficiente
			((camTargetMovementComp->getDirection() == LEFT) ||							//y cabes por la izquierda
			(cameraPos.getX() < limitX && camTargetMovementComp->getDirection() == RIGHT)))																		//y la derecha

			cameraPos.setX(cameraPos.getX() + actualTargetPos.getX() - lastTargetPosition.getX());	//te mueves

		if ((actualTargetPos.getY() > tilesToStartMoving && cameraPos.getY() > 0) && //si te has movido lo suficiente
			((camTargetMovementComp->getDirection() == UP) ||   //y cabes
			(cameraPos.getY() < limitY && camTargetMovementComp->getDirection() == DOWN)))

			cameraPos.setY(cameraPos.getY() + actualTargetPos.getY() - lastTargetPosition.getY());  //te mueves
			
		lastTargetPosition = actualTargetPos;
		
	}
}