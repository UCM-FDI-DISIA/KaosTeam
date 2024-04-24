#include "MovementComponent.h"
#include "../managers/MapManager.h"
#include "../scenes/Roomscene.h"
#include <iostream>


void MovementComponent::initComponent()
{
	tr = static_cast<TransformComponent * >(ent->getComponent(TRANSFORM_COMPONENT));
}

bool MovementComponent::checkIfTileWalkable(Vector2D v)
{
	return (ent->getScene()->getMapReader()->isTileWalkable(v)); //para comprobar q la tile existe
}

