#include "InventoryComponent.h"

InventoryComponent::InventoryComponent() : money(0) {}

MejorasData::MejorasData() : saltamontes(0), moscas(0), avispas(0), ciempies(0) {}
HabilidadesData::HabilidadesData() : gancho(false), sacoBombas(false) {};

int InventoryComponent::GetMoney() { return money; }

void InventoryComponent::AddMoney(int n) { money += n; }

/* "Gasta" el dinero.
* Si no es posible, devuelve false.
* Si es posible lo sustrae de la cantidad disponible y devuelve true.
*/
bool InventoryComponent::TakeMoney(int price)
{
	if (price > money)
		return false;

	money -= price;
	return true;
}