#include "MenuInicio.h"
#include "../sdlutils/SDLUtils.h"


MenuInicio::MenuInicio():Scene()
{
	menuBackground = new Texture(sdlutils().renderer(), "../Frog/resources/Menus/MainMenu.png",0,0);
	select = new Texture(sdlutils().renderer(), "../Frog/resources/Sprites/unframedemoska.png", 0, 0);
	dest.x = menuButton[0]->GetPosition().getX() - offsetX;
	dest.y = menuButton[0]->GetPosition().getY();
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
