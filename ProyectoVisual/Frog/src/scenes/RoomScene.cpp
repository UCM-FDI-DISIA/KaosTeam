#include "RoomScene.h"

void RoomScene::Render() {
	mapReader->draw(sdlutils().renderer());

	for (Entity* e : entityList) {
		if (e != nullptr)
			e->render();
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

RoomScene::~RoomScene() {
	//Eliminar la lista de entidades
	for (auto it = entityList.begin(); it != entityList.end(); ++it)
	{
		delete *it;
	}
}