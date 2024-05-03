#include "CogibleObjectComponent.h"
#include "ColliderComponent.h"
#include "InventoryComponent.h"

void CogibleObjectComponent::checkHit(Entity* e, Collider c) {
	if (e->getName() == FROG_ENTITY && c.getName() == TONGUE_COLLIDER) {
		//Pilla el inventario y le metes la mejora o habilidad
		//Una vez hecho esto, destruyes el objeto!
	}
}

void CogibleObjectComponent::initComponent() {
	static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->GetTransofmCollider()->AddCall([this](Entity* e, Collider c) {
		checkHit(e, c);
		});
};
