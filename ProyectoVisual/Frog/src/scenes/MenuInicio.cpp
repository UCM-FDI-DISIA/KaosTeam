#include "MenuInicio.h"

#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"


MenuInicio::MenuInicio(Game*g): Scene(false), game(g)
{
	im = InputManager::GetInstance();
	SDL_Rect buttonStartDest, buttonEndDest;

	//Valores de posicion temporales -> Hacerlos respecto al tama�o de pantalla
	//buttonEndDest.y hacerlo a partir de buttonStartDest.y + su size + offsetY
	buttonStartDest.w = buttonEndDest.w = WIN_WIDTH * 2 / 5;
	buttonStartDest.h = buttonEndDest.h = WIN_HEIGHT * 2 / 12;
	buttonStartDest.x = buttonEndDest.x = WIN_WIDTH / 2 - buttonStartDest.w / 2;
	buttonStartDest.y = WIN_HEIGHT * 4 / 8; buttonEndDest.y = WIN_HEIGHT * 5 / 7;
	

	menuBackground = new Texture(sdlutils().renderer(), "../Frog/resources/Menus/MainMenu.png",0,0);

	//Boton de Start
	menuButton.push_back(new Button(new Texture(sdlutils().renderer(), "../Frog/resources/Buttons/MenuJuego.png", 0, 0),
		buttonStartDest));
	menuButton[0]->connect([this]() {game->setScene(game->RUNNING); });
	//Boton de exit
	menuButton.push_back(new Button(new Texture(sdlutils().renderer(), "../Frog/resources/Buttons/MenuSalir.png", 0, 0),
		buttonEndDest));
	menuButton[1]->connect([this]() {game->exitGame(); });
	
	select = new Texture(sdlutils().renderer(), "../Frog/resources/Sprites/unframedemoska.png", 0, 0);

	dest.w = select->width();
	dest.h = select->height();
	dest.x = buttonStartDest.x - offsetX - dest.w / 2;
	dest.y = buttonStartDest.y + buttonStartDest.h / 2 - select->height() / 2;
};

void MenuInicio::render() {
	menuBackground->render(0,0);
	select->render(dest);
	for (auto it : menuButton)
		it->render();
}

void MenuInicio::update() {
	if (im->getAction1())
	{
		callButton();
	}
	if (im->getUp())
	{
		changeButton(ARRIBA);
	}
	else if (im->getDown())
	{
		changeButton(ABAJO);
	}
}

void MenuInicio::changeButton(bool dir)
{
	if (ARRIBA)
	{
		if (currentButton < 0) currentButton = menuButton.size() - 1;
		else currentButton -= 1;
	}
	else
		currentButton = (currentButton + 1) % menuButton.size();
	
	//Modifico posicion del cursor (mosca)
	dest.y = menuButton[currentButton]->getRect().y + menuButton[currentButton]->getRect().h / 2 - select->height() / 2;
}

void MenuInicio::callButton()
{
	menuButton[currentButton]->perform();
}
