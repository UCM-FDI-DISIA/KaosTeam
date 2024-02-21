#include "RoomScene.h"

void RoomScene::Render() {
	mapReader->draw(sdlutils().renderer());
	for (size_t i = 0; i < entityList.size(); i++) {
		entityList.at(i)->render();
	}
}

void RoomScene::Update() {
	for (size_t i = 0; i < entityList.size(); i++) {
		entityList.at(i)->update();
	}
}

void RoomScene::AddEntity(Entity* entity) {
	entityList.push_back(entity);
}