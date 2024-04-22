#include "ShopManager.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/InputManager.h"
#include "../sdlutils/Texture.h"
#include "../components/ShopComponent.h"
#include "../ecs/EntityShop.h"


Shop::Shop() : imngr(im()), grasshoperValue(10), waspValue(15), flyValue(15), centipedeValue(20),
							player(nullptr), playerMoney(nullptr), playerHUD(nullptr), playerInventory(nullptr),selected(nullptr),
							grasshoperTex(sdlutils().images().at("saltamontes")),
							waspTex(sdlutils().images().at("avispa")),
							flyTex(sdlutils().images().at("fly")),
							centipedeTex(sdlutils().images().at("ciempies")) {
	selectedPowerUp = GRASSHOPER;
	actualDirection = RIGHT;
	selected = grasshoper;
	initShopEntitys();
	setOppacity();
}
//Shop::~Shop() {
//	for (auto& a : animals) {
//		delete a;
//		a = nullptr;
//	}
//	delete selected;
//	selected = nullptr;
//	delete player;
//	player = nullptr;
//	delete playerMoney;
//	playerMoney = nullptr;
//	delete playerHUD;
//	playerHUD = nullptr;
//	delete playerInventory;
//	playerInventory = nullptr;
//
//}
void Shop::initShopEntitys() {
	ShopComponent* gShop = new ShopComponent(grasshoperTex, SDL_Rect{ 5,230,65,65 }, 1);
	grasshoper->addShopComponent(gShop);
	animals.push_back(grasshoper);
	ShopComponent* wShop = new ShopComponent(waspTex, SDL_Rect{87,155,65, 65 }, 1);
	wasp->addShopComponent(wShop);
	animals.push_back(wasp);
	ShopComponent* fShop = new ShopComponent(flyTex, SDL_Rect{ 170,180,flyTex.width(), flyTex.height() }, 3);
	fly->addShopComponent(fShop);
	animals.push_back(fly);
	ShopComponent* cShop = new ShopComponent(centipedeTex, SDL_Rect{ 245,230,65, 65 }, 1);
	centipede->addShopComponent(cShop);
	animals.push_back(centipede);
}
void Shop::setPlayer(Entity* player_) {
	player = player_;
	playerMoney = dynamic_cast<MoneyComponent*>(player->getComponent(MONEY_COMPONENT));
	playerInventory = dynamic_cast<InventoryComponent*>(player->getComponent(INVENTORY_COMPONENT));
}
void Shop::setHUD(HUDManager* hud) {
	playerHUD = hud;
}
void Shop::setSelectd() {
	ShopComponent* sC = selected->getShopComponent();
	sC->quitSelectd();
	switch (selectedPowerUp) {
	case Shop::GRASSHOPER:
	{
		ShopComponent* sC = grasshoper->getShopComponent();
		sC->setSelected();
		selected = grasshoper;
	}
	break;
	case Shop::WASP:
	{
		ShopComponent* sC = wasp->getShopComponent();
		sC->setSelected();
		selected = wasp;
	}
	break;
	case Shop::FLY:
	{
		ShopComponent* sC = fly->getShopComponent();
		sC->setSelected();
		selected = fly;
	}
	break;
	case Shop::CENTIPEDE:
	{
		ShopComponent* sC = centipede->getShopComponent();
		sC->setSelected();
		selected = centipede;
	}
	break;
	default:
		break;
	}
}
void Shop::setOppacity() {
	for (auto& a : animals) {
		ShopComponent* sC = a->getShopComponent();
		sC->setOppacity();
	}
}
void Shop::render() {
	for (auto& a : animals) {
		ShopComponent* sC = a->getShopComponent();
		sC->myRender();
	}
}
void Shop::update() {
	if (imngr.getActionBuy())
	{ buyPowerUp(selectedPowerUp); }
	else if (imngr.getActionRightShop()) { changeAnimal(RIGHT); }
	else if (imngr.getActionLeftShop()){ changeAnimal(LEFT); }

}
//este metodo se llamara cuando del input se reciba la tecla comprar y se pasa la mejora seleccionada en ese momento
void Shop::buyPowerUp(PowerUps powerUp) {
	bool buy = false;
	switch (powerUp) {
		case Shop::GRASSHOPER: 
		{	
			ShopComponent* sC = grasshoper->getShopComponent();
			if (!sC->isBuy() && playerMoney->TakeMoney(grasshoperValue)) {
				//activar salto largo

				playerInventory->buyJumpUpgrade();
				sC->setBuy();
				
			}
			else {
				std::cout << "no puedes comprar \n";
				//algo de dialogo
			}
		}	
		break;
		case Shop::WASP:
		{
			ShopComponent* sC = wasp->getShopComponent();
			if (!sC->isBuy() && playerMoney->TakeMoney(waspValue)) {
				//aumentar daño

				playerInventory->buyDamageUpgrade();
				sC->setBuy();
				
			}
			else {
				//algo de dialogo
			}
		}
		break;
		case Shop::FLY:
		{
			ShopComponent* sC = fly->getShopComponent();
			if (!sC->isBuy() && playerMoney->TakeMoney(flyValue)) {
				//aumentar vida
				playerHUD->ChangeMaxLife(2);
				sC->setBuy();
			}
			else {
				//algo de dialogo
			}
		}
		break;
		case Shop::CENTIPEDE:
		{
			ShopComponent* sC = centipede->getShopComponent();
			if (!sC->isBuy() && playerMoney->TakeMoney(centipedeValue)) {
				//aumentar alcance lengua
				std::cout << "ciempies \n";
				playerInventory->buyAttackUpgrade();
				sC->setBuy();
				
			}
			else {
				//algo de dialogo
			}
		}
		break;
		default:
			break;	
	}
	setOppacity();
}
void Shop::changeAnimal(Direction dir)
{
	int step = (dir == RIGHT) ? 1 : -1;
	int next = (static_cast<int>(selectedPowerUp) + step + TOTAL) % TOTAL;

	int numSteps = 0;
	while (animals[next]->getShopComponent()->isBuy()) {
		next = (next + step + TOTAL) % TOTAL;
		numSteps++;
		if (numSteps >= TOTAL) {
			return;
		}
	}
	selectedPowerUp = static_cast<PowerUps>(next);
	setSelectd();
	setOppacity();
	/*int p = 0;
	switch (dir) {
		case Shop::RIGHT: {
			p = ((int)selectedPowerUp + 1) % (int)TOTAL;
		}
		break;
	case Shop::LEFT: {
		if ((int)selectedPowerUp > 0) {
			p = ((int)selectedPowerUp - 1) % (int)TOTAL;
		}
		else {
			p = (int)TOTAL - 1;
		}
		}
		break;
	default:
	break;
	}
	selectedPowerUp = static_cast<PowerUps>(p);
	setSelectd();
	setOppacity();*/
}
