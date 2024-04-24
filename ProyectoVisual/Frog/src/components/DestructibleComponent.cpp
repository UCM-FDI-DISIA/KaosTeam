#include "DestructibleComponent.h"


DestructibleComponent::DestructibleComponent(int lootType) : loot(lootType)
{
	life = LifeComponent(1, 1);

}

void DestructibleComponent::update()
{
	//if (life.getactual() < 1)
	//{
	//	//destroy
	//}

}

void DestructibleComponent::DestructAndLoot()
{
	switch (loot)
	{
	case LOOT_RANDOM:

		break;
	case LOOT_VIDA:
		// spawnear vida
		break;
	case LOOT_DINERO:
		// spawnear dinero
		break;
	default:
		break;
	}

	//iniciar autodestruccion
}