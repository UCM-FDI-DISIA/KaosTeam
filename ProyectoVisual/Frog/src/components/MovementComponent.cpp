#include "MovementComponent.h"
#include "../managers/MapManager.h"
#include "../scenes/Roomscene.h"
#include <iostream>

MovementComponent::MovementComponent(Vector2D casilla, tile* t): posCasilla(casilla), destCasilla(casilla), actualTile(t)
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
}

void MovementComponent::initComponent()
{
	//actualTile = ent->getScene()->getMapReader()->getTile(posCasilla);
}

