#include "TransitionComponent.h"
#include "../scenes/RoomScene.h"
#include "ColliderComponent.h"

void TransitionComponent::changeMap()
{
	ent->getScene()->callForMapChange(nextMap, nextFlonk);
}

void TransitionComponent::CheckMapChange(Entity* e, Collider c) {
	if (e->getName() == FROG_ENTITY && c.getName() == TRANSFORM_COLLIDER && static_cast<MovementComponentFrog*>(e->getComponent(MOVEMENT_COMPONENT))->getMoveCompleted())
		changeMap();
};

TransitionComponent::TransitionComponent(std::string nextMap, flonkOrig nextFlonk) : nextMap(nextMap), nextFlonk(nextFlonk) {
};

void TransitionComponent::initComponent() {
	static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->GetTransformCollider()->AddCall([this](Entity* e, Collider c) { CheckMapChange(e, c); });
}
