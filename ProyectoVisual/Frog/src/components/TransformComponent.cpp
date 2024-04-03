#include "TransformComponent.h"

SDL_Rect TransformComponent::GetOnDisplayPosition() {
	int t = ent->getScene()->getMapReader()->getTileSize();
	SDL_Rect dest;

	Vector2D mOffset = offset + Vector2D((t - width) / 2, (t - height) / 2);//para que este centrado en la casilla
	Vector2D cameraPos = Camera::instance()->getCameraMovement();

	//Calcula la posición real en pantalla
	dest.x = casilla.getX() * t + mOffset.getX() - cameraPos.getX();
	dest.y = casilla.getY() * t + mOffset.getY() - cameraPos.getY();

	
	dest.w = width;
	dest.h = height;

	return dest;
}