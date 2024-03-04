#include "RoomScene.h"

void RoomScene::render() {
	mapReader->draw(sdlutils().renderer());

	for (Entity* e : entityList) {
		if (e != nullptr)
			e->render();
	}
}


void RoomScene::update() {
	for (Entity* e : entityList) {
		if (e != nullptr)
		e->update();
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
