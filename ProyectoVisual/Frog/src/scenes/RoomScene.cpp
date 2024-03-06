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
	cameraManager->update();
}

void RoomScene::createPlayer(std::string texPath, Vector2D pos)
{
	player = new Entity(this);
	player->addComponent(MOVEMENT_COMPONENT, new MovementComponent(pos));
	RenderComponent* rndr = new RenderComponent(texPath, 1, 1);
	rndr->setContext(player);
	player->addRenderComponent(rndr);
	entityList.push_back(player);

	AddEntity(player);
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
	delete cameraManager;
}
