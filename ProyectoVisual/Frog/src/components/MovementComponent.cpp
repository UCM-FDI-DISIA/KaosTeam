#include "MovementComponent.h"
#include "../managers/MapManager.h"
#include "../scenes/Roomscene.h"
#include <iostream>

MovementComponent::MovementComponent(Vector2D casilla, tile* t): posCasilla(casilla), actualTile(t)
{}

Vector2D MovementComponent::getPosition() {
	return posCasilla;
}

void MovementComponent::changePos(Vector2D v)
{
	posCasilla = v;
	actualTile->objInTile = nullptr;
	actualTile = ent->getScene()->getMapReader()->getTile(v);
	actualTile->objInTile = ent;
	cout << posCasilla;
}

void MovementComponent::initComponent()
{
	//actualTile = ent->getScene()->getMapReader()->getTile(posCasilla);
}

bool MovementComponent::checkIfTileWalkable(Vector2D v)
{
	return (ent->getScene()->getMapReader()->getTile(v) != nullptr); //para comprobar q la tile existe
}

