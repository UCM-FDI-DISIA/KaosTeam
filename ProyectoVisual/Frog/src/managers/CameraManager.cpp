#include "CameraManager.h"
#include "../scenes/RoomScene.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include <math.h>
Camera::~Camera() {
	camTarget = nullptr;
	targetTransform = nullptr;
	std::cout << "CAMERA DELETED" << std::endl;
}
void Camera::setTarget(Entity* target)
{
	camTarget = target;
	targetTransform = dynamic_cast<TransformComponent*>(camTarget->getComponent(TRANSFORM_COMPONENT));
	targetPosition = targetTransform->getCasilla() * tileSize;
	

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
	additionalOffset = targetTransform->getOffset();
	if (additionalOffset.getX() != 0)
		additionalOffset.setY(0);


	targetPosition = targetTransform->getCasilla() * tileSize + additionalOffset;
	cameraPos = { min(max((float)0, targetPosition.getX() - screenSize.getX() / 2), limitX - screenSize.getX()),
				  min(max((float)0, targetPosition.getY() - screenSize.getY() / 2), limitY - screenSize.getY()) };

	
}

Vector2D Camera::GetAdditionalOffset()
{
	return additionalOffset;
}
