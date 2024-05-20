#include "SwallowComponent.h"


SwallowComponent::SwallowComponent() : coll(nullptr), inv(nullptr), tr(nullptr), isPicked(false) {}

SwallowComponent::~SwallowComponent() {
	coll = nullptr;
	inv = nullptr;
	tr = nullptr;
}

void SwallowComponent::checkCollisionsTongue(Entity* e, Collider c) {
	if (e->getName() == FROG_ENTITY) {
		//Primero comprobamos si tiene la mejor de saco de bombas que permite tragarse objetos
		//(Luego miro la forma de usar el component CogibleObject que hizo Diego)
		if (static_cast<InventoryComponent*>(e->getComponent(INVENTORY_COMPONENT))->habilidades.sacoBombas) {
			if (c.getName() == TONGUE_COLLIDER) {
				//Ataque y transform de la rana
				//AttackComponentFrog* frogAt = static_cast<AttackComponentFrog*>(e->getComponent(ATTACK_COMPONENT));
				//TransformComponent* frogTr = static_cast<TransformComponent*>(e->getComponent(TRANSFORM_COMPONENT));

				//if (frogAt->attackHasHook() && frogTr->getCasilla() != tr->getCasilla()) {
				//	//Posicion de la rana
				//	tr->setCasilla(c.GetBox()->getCasilla());
				//}
				//Cuando llegue a la posicion de la rana, se elimina
				if (!isPicked) {
					static_cast<InventoryComponent*>(e->getComponent(INVENTORY_COMPONENT))->PickUpItem(BOMBAS, 1);
					ent->getScene()->removeEntity(this->ent);
					isPicked = true;
				}
			}
		}
	}

}

void SwallowComponent::initComponent(){
	coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));
	tr = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
	//este componente solo va adherido a las hormigas rojas de momento, pero podemos poner más entidades si hace falta
	if (ent->getName() == RED_ANT_ENTITY) { //Deben ser las Hormigas rojas
		coll->GetTransformCollider()->AddCall([this](Entity* e, Collider c) {checkCollisionsTongue(e, c); });
	}
}
