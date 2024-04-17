#pragma once
#ifndef SHOPMANAGER_H
#define SHOPMANAGER_H

#include "../ecs/Entity.h"
#include "../components/MoneyComponent.h"
#include "../utils/Singleton.h"

class InputManager;
class Texture;
class Shop : public Singleton<Shop> {

	friend Singleton<Shop>;
public:
	void render();
	void update();
	void setPlayer(Entity* player);
	//void enterShop();
	//void leaveShop();
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

	//Texture& currSelec; //Textura que apunta al boton seleccionado
	//SDL_Rect selecDest; 
	InputManager& imngr;
	//revisar & o *
	Texture& grasshoperTex;
	Texture& waspTex;
	Texture& flyTex;
	Texture& centipedeTex;
	//Texture& selectedTexture;

	//metodos
	Shop();
	void buyPowerUp(PowerUps powerUp);
	void changeButton(ButtonDirection dir);
	void setOppacity();
};
#endif // !SHOPMANAGER_H