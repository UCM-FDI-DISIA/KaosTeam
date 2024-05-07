#include "InventoryComponent.h"
#include "LifeComponent.h"

InventoryComponent::InventoryComponent() : money(0) {}

MejorasData::MejorasData() : saltamontes(0), moscas(0), avispas(0), ciempies(0), orbes(0) {}
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
		CurarVida(amm);
		break;
	case MOSCAS_DE_VIDA:
		MejoraMosca(amm);
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
	case ORBES:
		mejoras.orbes += 1;
		break;
	default:
		break;
	}
}

//Añadir las moscas por aquí, para que también añada la vida al life component, 1 mosca = 2 vidas
void InventoryComponent::MejoraMosca(int amm) {
	mejoras.moscas += amm;
	static_cast<LifeComponent*>(ent->getComponent(LIFE_COMPONENT))->AddMax(amm * 2);
}

//Cura la vida en el life component
void InventoryComponent::CurarVida(int amm) {
	static_cast<LifeComponent*>(ent->getComponent(LIFE_COMPONENT))->AddActual(amm);
}