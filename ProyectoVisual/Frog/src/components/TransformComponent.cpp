#include "TransformComponent.h"
#include "../scenes/RoomScene.h"
#include "../sdlutils/SDLUtils.h"

TransformComponent::TransformComponent(Vector2D casilla) : casilla(casilla) {
	width = 1.0;
	height = 1.0;
	offset = Vector2D(0, 0);
}

SDL_Rect TransformComponent::GetOnDisplayPosition() {
	int t = ent->getScene()->getMapReader()->getTileSize();
	int size = (int)t;

	SDL_Rect dest;

	Vector2D mOffset = offset + Vector2D((t - size) / 2, (t - size) / 2);//para que este centrado en la casilla
	Vector2D cameraPos = Camera::instance()->getCameraMovement();

	//Calcula la posición real en pantalla
	dest.x = casilla.getX() * t + mOffset.getX() - cameraPos.getX();
	dest.y = casilla.getY() * t + mOffset.getY() - cameraPos.getY();

	
	dest.w = size;
	dest.h = size;

	return dest;
}

void TransformComponent::resetPos(Vector2D v)
{
	casilla = v;
	ent->getScene()->getMapReader()->getTile(casilla)->objInTile = ent;
}

void TransformComponent::changePos(Vector2D v)
{
	ent->getScene()->getMapReader()->getTile(casilla)->objInTile = nullptr;
	casilla = v;
	ent->getScene()->getMapReader()->getTile(casilla)->objInTile = ent;
}
