#include "DestructibleComponent.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include "../sdlutils/SDLUtils.h"
#include "../scenes/RoomScene.h"

DestructibleComponent::DestructibleComponent(int lootType, Vector2D pos) : loot(lootType), rand_(sdlutils().rand()), position(pos)
{

}

void DestructibleComponent::update()
{


}

void DestructibleComponent::DestroySelf()
{
	int auxprob = rand_.nextInt(0, 100);
	switch (loot)
	{
	case LOOT_RANDOM:
		if(auxprob >= RandomLifeProb) {
			if(auxprob <= RandomLifeProb + RandomMoneyProb) SpawnLoot(LOOT_DINERO);
		}
		else SpawnLoot(LOOT_VIDA);
		break;

	case LOOT_VIDA:
		SpawnLoot(LOOT_VIDA);
		break;

	case LOOT_DINERO:
		SpawnLoot(LOOT_DINERO);
		break;

	default:
		break;
	}

	// TODO kms (destroy)
}

void DestructibleComponent::SpawnLoot(int loot)
	{
		
	}