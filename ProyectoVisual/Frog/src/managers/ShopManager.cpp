#include "ShopManager.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/InputManager.h"
#include "../sdlutils/Texture.h"
#include "../components/ShopComponent.h"
#include "../ecs/EntityShop.h"


Shop::Shop() : imngr(im()), grasshoperTex(sdlutils().images().at("saltamontes")),
							waspTex(sdlutils().images().at("avispa")),
							flyTex(sdlutils().images().at("fly")),
							centipedeTex(sdlutils().images().at("ciempies")) {
	selectedPowerUp = GRASSHOPER;
	actualDirection = RIGHT;
	selected = grasshoper;
	initShopEntitys();
	setOppacity();
}
void Shop::initShopEntitys() {
	ShopComponent* gShop = new ShopComponent(grasshoperTex, SDL_Rect{ 250,300,65,65 });
	grasshoper->addShopComponent(gShop);
	animals.push_back(grasshoper);
	ShopComponent* wShop = new ShopComponent(waspTex, SDL_Rect{ 330,300,65, 65 });
	wasp->addShopComponent(wShop);
	animals.push_back(wasp);
	ShopComponent* fShop = new ShopComponent(flyTex, SDL_Rect{ 410,300,flyTex.width(), flyTex.height() });
	fly->addShopComponent(fShop);
	animals.push_back(fly);
	ShopComponent* cShop = new ShopComponent(centipedeTex, SDL_Rect{ 480,300,65, 65 });
	centipede->addShopComponent(cShop);
	animals.push_back(centipede);
}
void Shop::setPlayer(Entity* player_) {
	player = player_;
	playerMoney = dynamic_cast<MoneyComponent*>(player->getComponent(MONEY_COMPONENT));
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
	else if (imngr.getActionRightShop()) { changeButton(RIGHT); }
	else if (imngr.getActionLeftShop()){ changeButton(LEFT); }

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
				std::cout << "mosca \n";
				
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
void Shop::changeButton(ButtonDirection dir)
{
	int p = 0;
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
	setOppacity();
}
