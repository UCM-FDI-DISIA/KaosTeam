#include "InventoryComponent.h"


InventoryComponent::InventoryComponent() : attackUpgrade(false),damageUpgrade(false), jumpUpgrade(false),entityActual(nullptr) {}
InventoryComponent::~InventoryComponent() {
	entityActual = nullptr;
}
void InventoryComponent::update(){
}