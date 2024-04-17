#include "ShopManager.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/InputManager.h"
#include "../sdlutils/Texture.h"


Shop::Shop() : imngr(im()), grasshoperTex(sdlutils().images().at("saltamontes")),
							waspTex(sdlutils().images().at("avispa")),
							flyTex(sdlutils().images().at("fly")),
							centipedeTex(sdlutils().images().at("ciempies"))/*,selectedTexture(grasshoperTex)*/ {
	selectedPowerUp = GRASSHOPER;
	actualDirection = RIGHT;
	setOppacity();
}
void Shop::setPlayer(Entity* player_) {
	player = player_;
	playerMoney = dynamic_cast<MoneyComponent*>(player->getComponent(MONEY_COMPONENT));
}
void Shop::setOppacity() {
	switch (selectedPowerUp) {
	case Shop::GRASSHOPER:
	{
		grasshoperTex.setAlphaMod(255);
		waspTex.setAlphaMod(200);
		flyTex.setAlphaMod(200);
		centipedeTex.setAlphaMod(200);
	}
	break;
	case Shop::WASP:
	{
		grasshoperTex.setAlphaMod(200);
		waspTex.setAlphaMod(255);
		flyTex.setAlphaMod(200);
		centipedeTex.setAlphaMod(200);
	}
	break;
	case Shop::FLY:
	{
		grasshoperTex.setAlphaMod(200);
		waspTex.setAlphaMod(200);
		flyTex.setAlphaMod(255);
		centipedeTex.setAlphaMod(200);
	}
	break;
	case Shop::CENTIPEDE:
	{
		grasshoperTex.setAlphaMod(200);
		waspTex.setAlphaMod(200);
		flyTex.setAlphaMod(200);
		centipedeTex.setAlphaMod(255);
	}
	break;
	default:
		break;
	}
}
void Shop::render() {
	
	//selectedTexture.setAlphaMod(255);

	//grasshoperTex.setAlphaMod(255);
	//waspTex.setAlphaMod(200);
	//flyTex.setAlphaMod(200);
	//centipedeTex.setAlphaMod(200);
	grasshoperTex.render(SDL_Rect{ 250,300,65,65 });
	waspTex.render(SDL_Rect{ 330,300,65, 65 });
	flyTex.render(SDL_Rect{ 410,300,flyTex.width(), flyTex.height() });
	centipedeTex.render(SDL_Rect{ 480,300,65, 65 });
	
}
void Shop::update() {
	if (imngr.getActionBuy()){ buyPowerUp(selectedPowerUp); }
	else if (imngr.getActionRightShop()) { changeButton(RIGHT); }
	else if (imngr.getActionLeftShop()){ changeButton(LEFT); }

}
//este metodo se llamara cuando del input se reciba la tecla comprar y se pasa la mejora seleccionada en ese momento
void Shop::buyPowerUp(PowerUps powerUp) {
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
	setOppacity();
	////Modifico la pos de la seleccion actual (mosca)
	//selecDest.x = menuButton[currButton]->getRect().x - offset - selecDest.w / 2;
	//selecDest.y = menuButton[currButton]->getRect().y + menuButton[currButton]->getRect().h / 2
	//	- currSelec.height() / 2;
}
