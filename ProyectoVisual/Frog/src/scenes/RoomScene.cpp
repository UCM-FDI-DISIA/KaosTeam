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
	//cameraManager->update();
}

void RoomScene::createPlayer(std::string texPath, Vector2D pos, int boundX, int boundY)
{
	player = new Entity(this);
	MovementComponent* mvm = new MovementComponentFrog(Vector2D(1,1));
	mvm->setContext(player);
	mvm->setBoundX(boundX);
	mvm->setBoundY(boundY);
	player->addComponent(MOVEMENT_COMPONENT, mvm);
	Texture* txtFrog = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/ranaSpritesheet.png", 4, 4);
	Texture* txtTongue = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/spritesheetTongue.png", 3, 1);
	RenderComponent* rndr = new RenderComponentFrog(txtFrog, txtTongue);
	rndr->setContext(player);
	player->addRenderComponent(rndr);
	Component* atck = new AttackComponentFrog();
	player->addComponent(ATTACK_COMPONENT, atck);
	atck->setContext(player);
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
