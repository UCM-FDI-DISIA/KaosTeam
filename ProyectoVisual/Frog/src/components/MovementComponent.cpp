#include "MovementComponent.h"
#include "../managers/MapManager.h"
#include "../scenes/Roomscene.h"
#include <iostream>

MovementComponent::MovementComponent(Vector2D casilla): posCasilla(casilla)
{}

Vector2D MovementComponent::getPosition() {
	return posCasilla;
}

void MovementComponent::changePos(Vector2D v)
{
	ent->getScene()->getMapReader()->getTile(posCasilla)->objInTile = nullptr;
	posCasilla = v;
	ent->getScene()->getMapReader()->getTile(posCasilla)->objInTile = ent;
	cout << posCasilla;
}

void MovementComponent::initComponent()
{
}

bool MovementComponent::checkIfTileWalkable(Vector2D v)
{
	return (ent->getScene()->getMapReader()->getTile(v) != nullptr); //para comprobar q la tile existe
}

