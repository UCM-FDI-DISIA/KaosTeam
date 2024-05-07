#include "InventoryComponent.h"
#include "LifeComponent.h"

InventoryComponent::InventoryComponent() : money(0), llaves(0) {
	mejoras = MejorasData();
	habilidades = HabilidadesData();
}

MejorasData::MejorasData() : saltamontes(0), moscas(0), avispas(0), ciempies(0), bombas(0), orbes(0) {}
HabilidadesData::HabilidadesData() : gancho(false), sacoBombas(true) {};

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
		mejoras.saltamontes++;
		break;
	case MOSCAS:
		CurarVida(amm);
		break;
	case MOSCAS_DE_VIDA:
		MejoraMosca(amm);
		break;
	case AVISPAS:
		mejoras.avispas++;
		break;
	case CIEMPIES:
		mejoras.ciempies++;
		break;
	case GANCHO:
		habilidades.gancho = true;
		break;
	case SACO_BOMBAS:
		habilidades.sacoBombas = true;
		//Llamada a el hud para actualizar el valor de sacoBombas
		break;
	case MONEDAS:
		PickMoneda(amm);
		break;
	case LLAVES:
		llaves++;
		//Llamar al hud para actualizar el valor
		break;
	case BOMBAS:
		mejoras.bombas += 1;
		std::cout << "\nNumero de bombas: " << mejoras.bombas << std::endl;
	case ORBES:
		mejoras.orbes += 1;
		break;
	//AQUI FALTA LA CABEZA DE LA CUCARACHA
	default:
		break;
	}
}

//Aï¿½adir las moscas por aquï¿½, para que tambiï¿½n aï¿½ada la vida al life component, 1 mosca = 2 vidas
void InventoryComponent::MejoraMosca(int amm) {
	mejoras.moscas += amm;
	static_cast<LifeComponent*>(ent->getComponent(LIFE_COMPONENT))->AddMax(amm * 2);
}

//Cura la vida en el life component
void InventoryComponent::CurarVida(int amm) {
	static_cast<LifeComponent*>(ent->getComponent(LIFE_COMPONENT))->AddActual(amm);
}

int InventoryComponent::GetLlaves()
{
	return llaves;
}

/// <summary>
/// Comprueba el tipo de moneda que ha llegado, a partir de eso añade la cantidad adecuada de monedas
/// </summary>
/// <param name="MonedaType (int)">El tipo de moneda</param>
void InventoryComponent::PickMoneda(int type) {
	switch (type)
	{
	case MONEDA_NARANJA:
		AddMoney(20);
		break;
	case MONEDA_MORADO:
		AddMoney(5);
		break;
	case MONEDA_ROSA:
		AddMoney(1);
		break;
	default:
		break;
	}
	//Llamar al hud para actualizar la cantidad de monedas que tiene el jugador
}