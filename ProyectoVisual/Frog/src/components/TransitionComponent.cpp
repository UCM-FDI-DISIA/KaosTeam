#include "TransitionComponent.h"
#include "../scenes/RoomScene.h"
#include "ColliderComponent.h"

void TransitionComponent::changeMap()
{
	ent->getScene()->callForMapChange(nextMap, nextFlonk);
}

void TransitionComponent::CheckMapChange(Entity* e, Collider c) {
	if (e->getName() == FROG_ENTITY && c.getName() == TRANSFORM_COLLIDER)
		changeMap();
};

TransitionComponent::TransitionComponent(std::string nextMap, flonkOrig nextFlonk) : nextMap(nextMap), nextFlonk(nextFlonk) {

};

void TransitionComponent::initComponent() {
	static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->GetTransofmCollider()->AddCall([this](Entity* e, Collider c) { CheckMapChange(e, c); });
}
