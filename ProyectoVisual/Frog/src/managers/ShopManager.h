#pragma once
#ifndef SHOPMANAGER_H
#define SHOPMANAGER_H

#include "../ecs/Entity.h"
#include "../components/MoneyComponent.h"
#include "../utils/Singleton.h"

class Shop : public Singleton<Shop> {

	friend Singleton<Shop>;
public:
	void render();
	void update();
	void setPlayer(Entity* player);
private:
	enum PowerUps { GRASSHOPER, WASP, FLY, CENTIPEDE };
	PowerUps selectedPowerUp;
	int grasshoperValue = 10; //saltamones
	int waspValue = 15; //avispa
	int flyValue = 15; //mosca
	int centipedeValue = 20; //ciempies
	Entity* player;
	MoneyComponent* playerMoney;
	Shop() {};
	void BuyPowerUp(PowerUps powerUp);
};
#endif // !SHOPMANAGER_H