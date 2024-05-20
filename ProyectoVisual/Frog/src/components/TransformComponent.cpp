#include "TransformComponent.h"
#include "../scenes/RoomScene.h"
#include "../sdlutils/SDLUtils.h"

TransformComponent::TransformComponent(Vector2D casilla) : Box(casilla) {}

TransformComponent::TransformComponent(Vector2D casilla, float width, float height) : Box(casilla, width, height) {}

TransformComponent::TransformComponent(Vector2D casilla, float width, float height, int scale) 
			: Box(casilla, width, height, scale) {}

void TransformComponent::resetPos(Vector2D v)
{
	casilla = v;
}

void TransformComponent::changePos(Vector2D v)
{
	if (ent->getScene()->getMapReader()->isTileWalkable(v)) {
		ent->getScene()->getMapReader()->getTile(casilla)->objInTile = nullptr;
		casilla = v;
		ent->getScene()->getMapReader()->getTile(casilla)->objInTile = ent;
	}
}
