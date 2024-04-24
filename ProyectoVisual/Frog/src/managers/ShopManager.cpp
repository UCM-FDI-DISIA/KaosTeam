#include "ShopManager.h"
#include "../sdlutils/SDLUtils.h"

void Shop::setPlayer(Entity* player_) {
	player = player_;
	playerMoney = dynamic_cast<MoneyComponent*>(player->getComponent(MONEY_COMPONENT));
}
void Shop::render() {
	//renderizar las mejoras?
}
void Shop::update() {

}
//este metodo se llamara cuando del input se reciba la tecla comprar y se pasa la mejora seleccionada en ese momento
void Shop::BuyPowerUp(PowerUps powerUp) {
	switch (powerUp) {
		case Shop::GRASSHOPER: 
		{
			if (playerMoney->TakeMoney(grasshoperValue)) {
				//activar salto largo
			}
			else {
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