#include "MenuInicio.h"

MenuInicio::MenuInicio() : Scene() {
	mapReader_ = new MapReader("tileMap_Prueba");
	mapReader_->load("resources/maps/tileMap_Prueba.tmx", sdlutils().renderer());
}

void MenuInicio::Render() {
	mapReader_->draw(sdlutils().renderer());
}

void MenuInicio::Update() {
	;
}