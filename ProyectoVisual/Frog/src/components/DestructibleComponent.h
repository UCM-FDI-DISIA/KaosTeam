#pragma once
#include "../components/LifeComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../scenes/RoomScene.h"


enum LootEnum { LOOT_RANDOM, LOOT_VIDA, LOOT_DINERO};

class DestructibleComponent
{
private:
	const int RandomLifeProb = 20, RandomMoneyProb = 20;
	int loot;	// Guarda lo que va a soltar cuando sea destruido
	RandomNumberGenerator& rand_;	//generador de numeros random
	Vector2D position;

	void DestroySelf();
	void SpawnLoot(int lootType);
	
public:
	DestructibleComponent(int lootType, Vector2D pos);
	void update();
};

