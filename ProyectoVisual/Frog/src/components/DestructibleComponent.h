#pragma once
#include "../components/LifeComponent.h"


enum LootEnum { LOOT_RANDOM,LOOT_VIDA, LOOT_DINERO};

class DestructibleComponent
{
private:
	LifeComponent life;
	int loot;	// probabilidad de que caiga tal 
							// cosa con el loot random sobre 100
	const int RandomLifeProb = 20, RandomMoneyProb = 20;
	void DestructAndLoot();
	

public:
	DestructibleComponent(int lootType);
	
	void update();
};

