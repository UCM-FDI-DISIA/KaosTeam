#include "CameraManager.h"

void Camera::setTarget(Entity* target)
{
	camTarget = target;
	camTargetMovementComp = dynamic_cast<MovementComponentFrog*>(camTarget->getComponent(MOVEMENT_COMPONENT));
	lastTargetPosition = camTargetMovementComp->getPosition();
}
void Camera::update() {

	Vector2D actualTargetPos = camTargetMovementComp->getPosition();
	if (lastTargetPosition.getX() != actualTargetPos.getX() && lastTargetPosition.getY() != actualTargetPos.getY()) {
		
		cameraPos.setX(cameraPos.getX() + lastTargetPosition.getX() - actualTargetPos.getX());
		cameraPos.setY(cameraPos.getY() + lastTargetPosition.getY() - actualTargetPos.getY());
		lastTargetPosition = actualTargetPos;
	}
}