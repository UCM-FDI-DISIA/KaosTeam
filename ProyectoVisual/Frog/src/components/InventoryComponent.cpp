#include "InventoryComponent.h"


InventoryComponent::InventoryComponent() : attackUpgrade(false),damageUpgrade(false), jumpUpgrade(false),entityActual(nullptr) {}
InventoryComponent::~InventoryComponent() {
	delete entityActual;
	entityActual = nullptr;
}
void InventoryComponent::update(){
}