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

//Mete un item en en el inventario
void InventoryComponent::PickUpItem(Items it, int amm = 1) {
	switch (it)
	{
	case SALTAMONTES:
		mejoras.saltamontes += 1;
		break;
	case MOSCAS:
		mejoras.moscas += 1;
		break;
	case AVISPAS:
		mejoras.avispas += 1;
		break;
	case CIEMPIES:
		mejoras.ciempies += 1;
		break;
	case GANCHO:
		habilidades.gancho = true;
		break;
	case BOMBAS:
		habilidades.sacoBombas = true;
		break;
	default:
		break;
	}
}