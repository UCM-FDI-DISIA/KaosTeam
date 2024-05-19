#include "CogibleObjectComponent.h"
#include "ColliderComponent.h"
#include "InventoryComponent.h"
#include "../scenes/RoomScene.h"

CogibleObjectComponent::CogibleObjectComponent()  {
	hitted = false;
	elapsedTime = 0;
}

CogibleObjectComponent::~CogibleObjectComponent() {
}
void CogibleObjectComponent::initComponent() {
	static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->GetTransofmCollider()->AddCall([this](Entity* e, Collider c) {
			checkHit(e, c);
		});
};

void CogibleObjectComponent::checkHit(Entity* e, Collider c) {
	if (!hitted && e->getName() == FROG_ENTITY && c.getName() == TONGUE_COLLIDER) {
		hitted = true;
		elapsedTime = sdlutils().virtualTimer().currTime();
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

void CogibleObjectComponent::update()
{
	//cuando pase el tiempo de espera podra volver a coger un item
	if (hitted && sdlutils().virtualTimer().currTime() > elapsedTime + WAIT_PICK) {
		hitted = false;
	}
}