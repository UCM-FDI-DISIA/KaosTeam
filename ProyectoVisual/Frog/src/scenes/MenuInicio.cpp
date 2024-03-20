#include "MenuInicio.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include"../managers/InputManager.h"
#include "../game/NewGameState.h"

#include "../game/Game.h"


MenuInicio::MenuInicio(Game* g, NewGameState* nGS): 
		Scene(), //
		newGSt(nGS), //
		imngr(im()), //
		game(g), //
		bg(sdlutils().images().at("background")), //Modificar
		currSelec(sdlutils().images().at("fly")), //Modificar
		width(WIN_WIDTH), height(WIN_HEIGHT), //
		currButton(0) //
{

	SDL_Rect buttonStartDest, buttonEndDest;
	
	//Valores de posicion temporales -> Hacerlos respecto al tama�o de pantalla
	//buttonEndDest.y hacerlo a partir de buttonStartDest.y + su size + offsetY
	buttonStartDest.w = buttonEndDest.w = width * 2 / 5;
	buttonStartDest.h = buttonEndDest.h = height * 2 / 12;
	buttonStartDest.x = buttonEndDest.x = width / 2 - buttonStartDest.w / 2;
	buttonStartDest.y = height * 4 / 8; buttonEndDest.y = height * 5 / 7;
	
	//Boton de Start
	menuButton.push_back(new Button(new Texture(sdlutils().renderer(), "../Frog/resources/Buttons/MenuJuego.png", 0, 0),
		buttonStartDest));
	menuButton[0]->connect([this]() { newGSt->enter(); });
	//Boton de exit
	menuButton.push_back(new Button(new Texture(sdlutils().renderer(), "../Frog/resources/Buttons/MenuSalir.png", 0, 0),
		buttonEndDest));
	menuButton[1]->connect([this]() { newGSt->leave(); });

	dest.w = currSelec.width();
	dest.h = currSelec.height();
	dest.x = buttonStartDest.x - offsetX - dest.w / 2;
	dest.y = buttonStartDest.y + buttonStartDest.h / 2 - currSelec.height() / 2;
}

void MenuInicio::render() {
	bg.render(SDL_Rect());
	currSelec.render(dest);
	for (auto it : menuButton)
		it->render();
}

void MenuInicio::update() {
	if (imngr.getAction1()) callButton();
	else if (imngr.getUp()) changeButton(ARRIBA);
	else if (imngr.getDown()) changeButton(ABAJO);
}

void MenuInicio::changeButton(bool dir)
{
	if (ARRIBA)
	{
		if (currButton < 0) currButton = menuButton.size() - 1;
		else currButton -= 1;
	}
	else currButton = (currButton + 1) % menuButton.size();
	
	//Modifico la pos de la seleccion actual (mosca)
	dest.y = menuButton[currButton]->getRect().y + menuButton[currButton]->getRect().h / 2 - currSelec.height() / 2;
}

void MenuInicio::callButton()
{
	menuButton[currButton]->perform();
}
