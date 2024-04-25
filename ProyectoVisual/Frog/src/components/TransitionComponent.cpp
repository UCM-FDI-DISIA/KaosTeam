#include "TransitionComponent.h"
#include "../scenes/RoomScene.h"

void TransitionComponent::changeMap()
{
	ent->getScene()->callForMapChange(nextMap, nextFlonk);
}