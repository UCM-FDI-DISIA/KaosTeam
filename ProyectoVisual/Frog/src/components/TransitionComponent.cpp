#include "TransitionComponent.h"
#include "../scenes/RoomScene.h"

void TransitionComponent::changeMap()
{
	ent->getScene()->changeMap(nextMap, nextFlonk);
}