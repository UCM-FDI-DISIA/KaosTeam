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

void RoomScene::createPlayer(std::string texPath, Vector2D pos, int boundX, int boundY)
{
	player = new Entity(this);
	Texture* txtFrog = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/ranaSpritesheet.png", 4, 4);
	Texture* txtTongue = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/spritesheetTongue.png", 3, 1);


	AnimationComponent* anim = new AnimationComponent(txtFrog, 4, 4);
	player->addComponent(ANIMATION_COMPONENT, anim);
	anim->setContext(player);

	Animation a; //Animaciones de la rana
	a = Animation({ Vector2D(0,0), Vector2D(0,1) }, false, false);
	anim->addAnimation("DOWN", a);
	a = Animation({ Vector2D(1,0), Vector2D(1,1) }, false, false);
	anim->addAnimation("UP", a);
	a = Animation({ Vector2D(2,0), Vector2D(2,1) }, false, false);
	anim->addAnimation("RIGHT", a);
	a = Animation({ Vector2D(2,0), Vector2D(2,1) }, true, false);
	anim->addAnimation("LEFT", a);

	MovementComponent* mvm = new MovementComponentFrog(Vector2D(2, 2), anim);
	mvm->setContext(player);
	mvm->setBoundX(boundX);
	mvm->setBoundY(boundY);
	player->addComponent(MOVEMENT_COMPONENT, mvm);
	
	RenderComponent* rndr = new RenderComponentFrog(txtFrog, txtTongue, anim);
	rndr->setContext(player);
	player->addRenderComponent(rndr);

	Component* atck = new AttackComponentFrog();
	player->addComponent(ATTACK_COMPONENT, atck);
	atck->setContext(player);

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
