#include "MenuInicio.h"

#include "../sdlutils/SDLUtils.h"



MenuInicio::MenuInicio():Scene()
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
	menuButton.push_back( new Button(new Texture(sdlutils().renderer(), "../Frog/resources/Buttons/MenuJuego.png", 0, 0),
		buttonStartDest));
	menuButton.push_back( new Button(new Texture(sdlutils().renderer(), "../Frog/resources/Buttons/MenuSalir.png", 0, 0),
		buttonEndDest));
	select = new Texture(sdlutils().renderer(), "../Frog/resources/Sprites/unframedemoska.png", 0, 0);

	dest.w = select->width();
	dest.h = select->height();
	dest.x = menuButton[0]->getRect().x - offsetX - dest.w / 2;
	dest.y = menuButton[0]->getRect().y + menuButton[0]->getTexture()->height() / 2;
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
		
	}
	if (im->getUp())
	{
		std::cout << "ohno";
	}
	else if (im->getDown())
	{

	}
}

void MenuInicio::changeButton(bool dir)
{
	if (ARRIBA)
	{
		currentButton -= 1;
		
		if (currentButton < 0)
			currentButton = menuButton.size() - 1;
	}
	else
		currentButton = (currentButton + 1) % menuButton.size();
	
}

void MenuInicio::callButton()
{
	menuButton[currentButton]->perform();
}
