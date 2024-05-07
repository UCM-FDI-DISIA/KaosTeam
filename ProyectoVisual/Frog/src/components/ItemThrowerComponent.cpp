#include "ItemThrowerComponent.h"

ItemThrowerComponent::ItemThrowerComponent() : inv(nullptr) {
}

ItemThrowerComponent::~ItemThrowerComponent() {
}

void ItemThrowerComponent::initComponent() {
	//Accedemos al inventario del jugador
	inv = static_cast<InventoryComponent*>(ent->getScene()->getPlayer()->getComponent(INVENTORY_COMPONENT));

}

void ItemThrowerComponent::throwItem(Items object) {


}
