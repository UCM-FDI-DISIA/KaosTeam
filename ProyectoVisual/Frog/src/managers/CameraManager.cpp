#include "CameraManager.h"
#include "../scenes/RoomScene.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include <math.h>

void Camera::setTarget(Entity* target)
{
	camTarget = target;
	camTargetMovementComp = dynamic_cast<MovementComponentFrog*>(camTarget->getComponent(MOVEMENT_COMPONENT));
	lastTargetPosition = camTargetMovementComp->getPosition();

	tileSize = target->getScene()->getMapReader()->getTileSize();
	screenSize = { round(WIN_WIDTH / (float)tileSize), round(WIN_HEIGHT / (float)tileSize) }; //calcular cuantas tiles hay en la pantalla
	limitX = target->getScene()->getMapReader()->getCols();
	limitY = target->getScene()->getMapReader()->getRows();


	
	


	//ese min max es para hayar el valor medio, xq 0 < pos < limit
	cameraPos = { min(max((float)0, lastTargetPosition.getX()- screenSize.getX()/2), limitX - screenSize.getX()),
				  min(max((float)0, lastTargetPosition.getY() - screenSize.getY() / 2), limitY - screenSize.getY()) };

}
void Camera::update() {

	Vector2D actualTargetPos = camTargetMovementComp->getPosition();
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


	////calcular el ofset
	//additionalOffset = camTargetMovementComp->getOffset();
	//if (cameraPos.getX() == 0 || cameraPos.getX() >= limitX - screenSize.getX())
	//	additionalOffset.setX(0);

	//if(cameraPos.getY() == 0 || cameraPos.getY() >= limitY - screenSize.getY())
	//	additionalOffset.setX(0);
	
}




Vector2D Camera::GetAdditionalOffset()
{
	return additionalOffset;
}
