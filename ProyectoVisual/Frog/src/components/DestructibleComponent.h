#pragma once
#include "../ecs/Component.h"
#include "../scenes/RoomScene.h"
#include "ColliderComponent.h"
#include "MovementComponentFrog.h"


enum LootEnum {LOOT_RANDOM, LOOT_VIDA, LOOT_DINERO};

class DestructibleComponent :public Component
{
private:
	const int RandomLifeProb = 20, RandomMoneyProb = 20;	//Probabilidad sobre 100 de que suelte tal cosa
	int loot;												//Guarda lo que va a soltar cuando sea destruido
	RandomNumberGenerator& rand_;							//Generador de numeros random
	Vector2D position;						 				//Posicion para dropear loot al morir
	ColliderComponent* coll = nullptr;
	RoomScene* scen = nullptr;

	void LootAndBreak();
	void CheckCollisions(Entity* ent, Collider c);
	
public:
	DestructibleComponent(int lootType, Vector2D pos);
	//virtual ~DestructibleComponent();
	void initComponent() override;
};

