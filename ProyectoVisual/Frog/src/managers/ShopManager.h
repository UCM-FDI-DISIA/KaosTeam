#pragma once
#ifndef SHOPMANAGER_H
#define SHOPMANAGER_H

#include "../components/InventoryComponent.h"
#include "../utils/Singleton.h"
#include <vector>
#include "../ecs/EntityShop.h"
#include "../managers/HUDManager.h"
/*
* Clase que gestiona la compra de objetos en la tienda
*/
class InputManager;
class Texture;
class Shop : public Singleton<Shop> {

	friend Singleton<Shop>;
public:
	void render();
	void update();
	void setPlayer(Entity* player);
	void setHUD(HUDManager* hud);
	virtual ~Shop();
private:

	enum PowerUps { GRASSHOPER, WASP, FLY, CENTIPEDE, TOTAL };
	PowerUps selectedPowerUp;
	enum Direction { RIGHT, LEFT };	//para saber en que direccion estamos cambiando entre los objetos para comprar
	Direction actualDirection;

	int grasshoperValue; //saltamones
	int waspValue; //avispa
	int flyValue; //mosca
	int centipedeValue; //ciempies

	Entity* player;
	HUDManager* playerHUD;
	InventoryComponent* playerInventory;
 
	InputManager& imngr;

	//entidades que se pueden comprar
	EntityShop* grasshoper = new EntityShop();
	EntityShop* wasp = new EntityShop();
	EntityShop* fly = new EntityShop();
	EntityShop* centipede = new EntityShop();
	EntityShop* selected;
	//texturas
	Texture& grasshoperTex;
	Texture& waspTex;
	Texture& flyTex;
	Texture& centipedeTex;
	Texture& pricesTex;
	Texture& birdTex;
	Texture& inputTex;
	std::vector<EntityShop*> animals;
	bool change = false;
	//metodos
	Shop();
	
	void buyPowerUp(PowerUps powerUp);	
	void changeAnimal(Direction dir); 
	void setOppacity();
	void setSelected();
	void initShopEntitys();
	void changeTexture();

	const Uint32 CHANGE_TIME = 3000; //cambiar el recuadro de dialogo del pajaro cada 3 segundos
	Uint32 lastChangeTexture;	
};
#endif // !SHOPMANAGER_H