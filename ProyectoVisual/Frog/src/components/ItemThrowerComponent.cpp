#include "ItemThrowerComponent.h"

ItemThrowerComponent::ItemThrowerComponent() : inv(nullptr), playerTr(nullptr) {
}

ItemThrowerComponent::~ItemThrowerComponent() {
	inv = nullptr;
	playerTr = nullptr;
}

void ItemThrowerComponent::initComponent() {
	//Accedemos al inventario del jugador
	inv = static_cast<InventoryComponent*>(ent->getScene()->getPlayer()->getComponent(INVENTORY_COMPONENT));
	playerTr = static_cast<TransformComponent*>(ent->getScene()->getPlayer()->getComponent(TRANSFORM_COMPONENT));
}

void ItemThrowerComponent::throwItem(Items object, MovementComponentFrog* mvFrog) {
	Vector2D dir;
	switch (mvFrog->getDirection()) {
	case DOWN:
		dir = Vector2D(0, 1);
		break;
	case UP:
		dir = Vector2D(0, -1);
		break;
	case LEFT:
		dir = Vector2D(-1, 0);
		break;
	case RIGHT:
		dir = Vector2D(1, 0);
		break;
	}

	switch (object) {
	case BOMBAS:
		ent->getScene()->createBomb(playerTr->getCasilla() + dir);
		inv->mejoras.bombas--;
		std::cout << "\nNumero de bombas (tras lanzar 1): " << inv->mejoras.bombas << std::endl;
		break;
	case ROACH_HEAD:
		ent->getScene()->createHeadCockroach(playerTr->getCasilla() + dir, true);
		inv->mejoras.roach_head--;
		break;
	//Haria falta otro caso más para el orbe (o definir otro boton para que lance el orbe en concreto)
	/*case ORBE:
		break;*/
	default:
		break;
	}


}

void ItemThrowerComponent::throwStart() {
	static_cast<RenderComponentFrog*>(ent->getRenderComponentFrog())->ThrowStart();
}
