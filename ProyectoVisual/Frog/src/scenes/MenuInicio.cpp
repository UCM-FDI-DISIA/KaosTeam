#include "MenuInicio.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"


MenuInicio::MenuInicio(Game*g):Scene(), game(g)
{
	im = InputManager::GetInstance();
	SDL_Rect buttonStartDest, buttonEndDest;

	//Valores de posicion temporales -> Hacerlos respecto al tama�o de pantalla
	//buttonEndDest.y hacerlo a partir de buttonStartDest.y + su size + offsetY
	buttonStartDest.x = 150; buttonStartDest.y = 250; buttonEndDest.x = 150; buttonEndDest.y = 400;
	buttonStartDest.w = buttonEndDest.w = 300; buttonStartDest.h = buttonEndDest.h = 100;

	menuBackground = new Texture(sdlutils().renderer(), "../Frog/resources/Menus/MainMenu.png",0,0);
	Button* aux = new Button(new Texture(sdlutils().renderer(), "../Frog/resources/Buttons/MenuJuego.png", 0, 0),
		buttonStartDest);
	aux->connect([this]() {game->changeScene(); });
	menuButton.push_back( aux);
	aux = new Button(new Texture(sdlutils().renderer(), "../Frog/resources/Buttons/MenuSalir.png", 0, 0),
		buttonEndDest);
	aux->connect([this]() {game->exitGame(); });
	menuButton.push_back( aux);
	
	select = new Texture(sdlutils().renderer(), "../Frog/resources/Sprites/unframedemoska.png", 0, 0);

	dest.x = menuButton[0]->getRect().x - offsetX;
	dest.y = menuButton[0]->getRect().y + menuButton[0]->getTexture()->height() / 2;
	dest.w = 37;
	dest.h = 25;
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
		std::cout << "hola";
		changeButton(ARRIBA);
	}
	else if (im->getDown())
	{
		//changeButton(ABAJO);
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
