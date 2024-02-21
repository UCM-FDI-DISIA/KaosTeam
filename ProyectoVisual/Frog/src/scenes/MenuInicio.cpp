#include "MenuInicio.h"

MenuInicio::MenuInicio() : Scene() {
	mapReader_ = new MapComponent("tileMap_Prueba");
	mapReader_->load("resources/maps/tileMap_Prueba.tmx", sdlutils().renderer());

	player_ = new Entity();
	player_->addComponent(MOVEMENT_COMPONENT, new MovementComponent());
	player_->addComponent(RENDER_COMPONENT, new RenderComponent("../Frog/resources/sprites/unFrameDeRana.png", 1, 1));
}

void MenuInicio::Render() {
	mapReader_->draw(sdlutils().renderer());

	player_->render();
}

void MenuInicio::Update() {
	;
}