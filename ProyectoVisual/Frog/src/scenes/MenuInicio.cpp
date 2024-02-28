#include "MenuInicio.h"
#include "../sdlutils/Texture.h"
MenuInicio::MenuInicio() : Scene() {

	//mapReader_ = new MapManager("tileMap_Prueba");
	//mapReader_->load("resources/maps/tileMap_Prueba.tmx", sdlutils().renderer());
}

MenuInicio::MenuInicio(Texture* menuBG):menuBackground(menuBG)
{
};

void MenuInicio::Render() {
	menuBackground->render(0,0);
}

void MenuInicio::Update() {
	;
}
