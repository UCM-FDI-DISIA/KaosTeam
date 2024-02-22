#include "RoomScene.h"

RoomScene::RoomScene() : Scene() {
	mapReader_ = new MapManager("tileMap_Prueba");
	mapReader_->load("resources/maps/tileMap_Prueba.tmx", sdlutils().renderer());

	Entity* player = new Entity(this);
	Vector2D v(2, 2);
	player->addComponent(MOVEMENT_COMPONENT, new MovementComponent(v));
	RenderComponent* rndr = new RenderComponent("../Frog/resources/sprites/unFrameDeRana.png", 1, 1);
	rndr->setContext(player);
	player->addComponent(RENDER_COMPONENT, rndr);
	entityList.push_back(player);
}

void RoomScene::Render() {
	mapReader_->draw(sdlutils().renderer());

	for (Entity* e : entityList) {
		if (e != nullptr)
			e->render();
	}
}

void RoomScene::Update() {
	;
}