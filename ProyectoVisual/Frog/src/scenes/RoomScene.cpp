#include "RoomScene.h"

RoomScene::RoomScene() : Scene() {
	mapReader = new MapComponent("tileMap_Prueba");
	mapReader->load("resources/maps/tileMap_Prueba.tmx", sdlutils().renderer());
}

void RoomScene::Render() {
	mapReader->draw(sdlutils().renderer());
}

void RoomScene::Update() {
	;
}