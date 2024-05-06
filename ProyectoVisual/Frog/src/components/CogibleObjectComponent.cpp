#include "CogibleObjectComponent.h"
#include "ColliderComponent.h"
#include "InventoryComponent.h"
#include "../scenes/RoomScene.h"

void CogibleObjectComponent::initComponent() {
	static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->GetTransofmCollider()->AddCall([this](Entity* e, Collider c) {
			checkHit(e, c);
		});
};

void CogibleObjectComponent::checkHit(Entity* e, Collider c) {
	if (e->getName() == FROG_ENTITY && c.getName() == TONGUE_COLLIDER) {
		PickUpItem();
	}
}

void CogibleObjectComponent::PickUpItem() {

}

CogibleObjectComponent::CogibleObjectComponent() {
	itemAmmount = 1;
}

CogibleObjectComponent::CogibleObjectComponent(int ammount) {
	itemAmmount = ammount;
}