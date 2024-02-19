#include "RoomScene.h"

RoomScene::RoomScene() : Scene() {
	mapReader_ = new MapComponent("tileMap_Prueba");
	mapReader_->load("resources/maps/tileMap_Prueba.tmx", sdlutils().renderer());
}

void RoomScene::Render() {
	mapReader_->draw(sdlutils().renderer());
}

void RoomScene::Update() {
	;
}