#include "MenuInicio.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"


MenuInicio::MenuInicio():Scene()
{
	menuBackground = new Texture(sdlutils().renderer(), "../Frog/resources/Menus/MainMenu.png",0,0);
};

void MenuInicio::Render() {
	menuBackground->render(0,0);
}

void MenuInicio::Update() {

}
