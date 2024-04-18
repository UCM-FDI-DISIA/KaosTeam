#include "MovementComponent.h"
#include "../managers/MapManager.h"
#include "../scenes/Roomscene.h"
#include <iostream>

void MovementComponent::initComponent()
{
	tr = ent->getComponent<TransformComponent>(TRANSFORM_COMPONENT);
}

bool MovementComponent::checkIfTileWalkable(Vector2D v)
{
	return (ent->getScene()->getMapReader()->isTileWalkable(v)); //para comprobar q la tile existe
}

