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
		e->getScene()->removeEntity(this->ent);
	}
}

void CogibleObjectComponent::PickUpItem() {
	InventoryComponent* ic = static_cast<InventoryComponent*>(ent->getScene()->getPlayer()->getComponent(INVENTORY_COMPONENT));
	ic->PickUpItem(item, itemAmmount);
}

CogibleObjectComponent::CogibleObjectComponent(Items it) {
	itemAmmount = 1;
	item = it;
}

CogibleObjectComponent::CogibleObjectComponent(Items it, int ammount) {
	itemAmmount = ammount;
	item = it;
}