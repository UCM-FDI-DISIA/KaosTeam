#include "InventoryComponent.h"


InventoryComponent::InventoryComponent() : attackUpgrade(false),damageUpgrade(false), jumpUpgrade(true),entityActual(nullptr) {}
InventoryComponent::~InventoryComponent() {
	entityActual = nullptr;
}
void InventoryComponent::update(){
}