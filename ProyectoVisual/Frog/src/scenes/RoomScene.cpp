#include "RoomScene.h"

void RoomScene::Render() {
	mapReader->draw(sdlutils().renderer());

	for (Entity* e : entityList) {
		if (e != nullptr)
			e->render();
	}
}

void RoomScene::Update() {
	for (Entity* e : entityList) {
		if (e != nullptr)
		e->update();
	}
	cameraManager->update();
}

void RoomScene::AddEntity(Entity* entity) {
	entityList.push_back(entity);
}
//void RoomScene::HandleEvents(const SDL_Event& event) {
//	cameraManager->handleEvents(event);
//}
RoomScene::~RoomScene() {
	//Eliminar la lista de entidades
	for (auto it = entityList.begin(); it != entityList.end(); ++it)
	{
		delete *it;
	}
	delete cameraManager;
}
