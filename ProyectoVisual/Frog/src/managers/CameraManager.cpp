#include "CameraManager.h"
#include "../scenes/RoomScene.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include <math.h>

void Camera::setTarget(Entity* target)
{
	camTarget = target;
	targetPosition = camTargetMovementComp->getPosition()*tileSize;
	direction = camTargetMovementComp->getDirection();
	targetTransform = dynamic_cast<TransformComponent*>(camTarget->getComponent(TRANSFORM_COMPONENT));
	lastTargetPosition = targetTransform->getCasilla();

	tileSize = target->getScene()->getMapReader()->getTileSize();
	screenSize = {WIN_WIDTH, WIN_HEIGHT };
	limitX = target->getScene()->getMapReader()->getCols() * tileSize;
	limitY = target->getScene()->getMapReader()->getRows() * tileSize;

	tilesToStartMovingX = screenSize.getX() / 2;
	tilesToStartMovingY = screenSize.getY() / 2;


	//ese min max es para hayar el valor medio, xq 0 < pos < limit
	cameraPos = { min(max((float)0, targetPosition.getX()- screenSize.getX()/2), limitX - screenSize.getX()),
				  min(max((float)0, targetPosition.getY()- screenSize.getY() / 2), limitY - screenSize.getY()) };

}
void Camera::update() {

	//calcular el offset para q no salte con la rana
	additionalOffset = camTargetMovementComp->getOffset();
	if (additionalOffset.getX() != 0)
		additionalOffset.setY(0);
	Vector2D actualTargetPos = targetTransform->getCasilla();
	if (lastTargetPosition.getX() != actualTargetPos.getX() || lastTargetPosition.getY() != actualTargetPos.getY()) {
		
		if ((cameraPos.getX() > 0 || actualTargetPos.getX() > tilesToStartMoving) &&				//si no te sales por la izquierda
			(cameraPos.getX() < limitX - screenSize.getX() || actualTargetPos.getX() < limitX - tilesToStartMoving)) //ni la derecha
		{
			cameraPos.setX(cameraPos.getX() + actualTargetPos.getX() - lastTargetPosition.getX());
		}
			

		if ((cameraPos.getY() > 0 || actualTargetPos.getY() > 2) &&				//si no te sales por arriba
			(cameraPos.getY() < limitY - screenSize.getY() || actualTargetPos.getY() < limitY - 2)) //ni por abajo
		{
			cameraPos.setY(cameraPos.getY() + actualTargetPos.getY() - lastTargetPosition.getY());  
		}
			
		lastTargetPosition = actualTargetPos;
		
	}


	targetPosition = camTargetMovementComp->getPosition() * tileSize + additionalOffset;
	cameraPos = { min(max((float)0, targetPosition.getX() - screenSize.getX() / 2), limitX - screenSize.getX()),
				  min(max((float)0, targetPosition.getY() - screenSize.getY() / 2), limitY - screenSize.getY()) };

	
}




Vector2D Camera::GetAdditionalOffset()
{
	return additionalOffset;
}
