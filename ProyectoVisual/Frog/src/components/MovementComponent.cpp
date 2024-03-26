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
	Entity* objEnDestino = ent->getScene()->getMapReader()->getTile(posCasilla)->objInTile;
	if (objEnDestino != nullptr){
		if (objEnDestino->getComponent(TRANSITION_COMPONENT) != nullptr){
			//COLISION CON OBJETO DE TRANSICION PROVISIONAL
			static_cast<TransitionComponent*>(objEnDestino->getComponent(TRANSITION_COMPONENT))->changeMap();
		}
		else {
			ent->getScene()->getMapReader()->getTile(posCasilla)->objInTile = ent;
		}
	}
	else {
		ent->getScene()->getMapReader()->getTile(posCasilla)->objInTile = ent;
	}
	cout << posCasilla;
}

void MovementComponent::resetPos(Vector2D v)
{
	posCasilla = v;
	ent->getScene()->getMapReader()->getTile(posCasilla)->objInTile = ent;
}

void MovementComponent::initComponent()
{
}

bool MovementComponent::checkIfTileWalkable(Vector2D v)
{
	return (ent->getScene()->getMapReader()->getTile(v) != nullptr); //para comprobar q la tile existe
}

