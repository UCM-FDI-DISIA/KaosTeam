#pragma once
#include "../components/LifeComponent.h"
//#include "../sdlutils/SDLUtils.h"
#include "../scenes/RoomScene.h"
#include "ColliderComponent.h"
#include "MovementComponentFrog.h"


enum LootEnum {LOOT_RANDOM, LOOT_VIDA, LOOT_DINERO};

class DestructibleComponent
{
private:
	const int RandomLifeProb = 20, RandomMoneyProb = 20;	//probabilidad sobre 100 de que suelte tal cosa
	int loot;												// Guarda lo que va a soltar cuando sea destruido
	RandomNumberGenerator& rand_;							//generador de numeros random
	Vector2D position;										//posicion para cuando dropee el loot al morir

	void DestroySelf();
	void SpawnLoot(int lootType);
	void CheckCollisions(Entity* ent, Collider c);
	
public:
	DestructibleComponent(int lootType, Vector2D pos);
};

