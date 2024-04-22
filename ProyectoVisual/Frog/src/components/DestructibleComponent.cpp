#include "DestructibleComponent.h"
//using namespace DestructibleComponent;


DestructibleComponent::DestructibleComponent(int lootType) : loot(lootType)
{
	//life = LifeComponent(1, 1);
	const int RandomLifeProb = 20, RandomMoneyProb = 20;

}

void update()
{
	//if (life.getactual() < 1)
	//{
	//	//destroy
	//}

}

void destructAndLoot()
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