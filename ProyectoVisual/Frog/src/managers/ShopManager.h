#pragma once
#ifndef SHOPMANAGER_H
#define SHOPMANAGER_H

#include "../components/MoneyComponent.h"
#include "../utils/Singleton.h"
#include <vector>
#include "../ecs/EntityShop.h"

class InputManager;
class Texture;
class Shop : public Singleton<Shop> {

	friend Singleton<Shop>;
public:
	void render();
	void update();
	void setPlayer(Entity* player);
private:

	enum PowerUps { GRASSHOPER, WASP, FLY, CENTIPEDE, TOTAL };
	PowerUps selectedPowerUp;
	enum ButtonDirection { RIGHT, LEFT };
	ButtonDirection actualDirection;

	int grasshoperValue = 10; //saltamones
	int waspValue = 15; //avispa
	int flyValue = 15; //mosca
	int centipedeValue = 20; //ciempies

	Entity* player = nullptr;
	MoneyComponent* playerMoney = nullptr;
 
	InputManager& imngr;

	EntityShop* grasshoper = new EntityShop();
	EntityShop* wasp = new EntityShop();
	EntityShop* fly = new EntityShop();
	EntityShop* centipede = new EntityShop();
	EntityShop* selected = nullptr;
	Texture& grasshoperTex;
	Texture& waspTex;
	Texture& flyTex;
	Texture& centipedeTex;
	std::vector<EntityShop*> animals;

	//metodos
	Shop();
	void buyPowerUp(PowerUps powerUp);
	void changeButton(ButtonDirection dir);
	void setOppacity();
	void setSelectd();
	void initShopEntitys();
};
#endif // !SHOPMANAGER_H