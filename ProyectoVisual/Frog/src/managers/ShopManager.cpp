#include "ShopManager.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/InputManager.h"
Shop::Shop() : imngr(im()) {
	selectedPowerUp = GRASSHOPER;
	actualDirection = RIGHT;
}
void Shop::setPlayer(Entity* player_) {
	player = player_;
	playerMoney = dynamic_cast<MoneyComponent*>(player->getComponent(MONEY_COMPONENT));
}
void Shop::render() {
	/*for (auto it : buttons)
		it->render();*/
}
void Shop::update() {
	if (imngr.getActionBuy()){ BuyPowerUp(selectedPowerUp); }
	else if (imngr.getActionRightShop()) { changeButton(RIGHT); }
	else if (imngr.getActionLeftShop()){ changeButton(LEFT); }
		

}
//este metodo se llamara cuando del input se reciba la tecla comprar y se pasa la mejora seleccionada en ese momento
void Shop::BuyPowerUp(PowerUps powerUp) {
	switch (powerUp) {
		case Shop::GRASSHOPER: 
		{	
			if (playerMoney->TakeMoney(grasshoperValue)) {
				//activar salto largo
				std::cout << "puedes comprar \n";
			}
			else {
				std::cout << "no puedes comprar \n";
				//algo de dialogo
			}
		}	
		break;
		case Shop::WASP:
		{
			if (playerMoney->TakeMoney(waspValue)) {
				//aumentar daño
			}
			else {
				//algo de dialogo
			}
		}
		break;
		case Shop::FLY:
		{
			if (playerMoney->TakeMoney(flyValue)) {
				//aumentar vida
			}
			else {
				//algo de dialogo
			}
		}
		break;
		case Shop::CENTIPEDE:
		{
			if (playerMoney->TakeMoney(centipedeValue)) {
				//aumentar alcance lengua
			}
			else {
				//algo de dialogo
			}
		}
		break;
		default:
			break;	
	}
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
		p = ((int)selectedPowerUp - 1) % (int)TOTAL;
	}
	break;
	default:
		break;
	}
	selectedPowerUp = static_cast<PowerUps>(p);
	////Modifico la pos de la seleccion actual (mosca)
	//selecDest.x = menuButton[currButton]->getRect().x - offset - selecDest.w / 2;
	//selecDest.y = menuButton[currButton]->getRect().y + menuButton[currButton]->getRect().h / 2
	//	- currSelec.height() / 2;
}
