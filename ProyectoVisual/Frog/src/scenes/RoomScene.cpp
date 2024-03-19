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

void RoomScene::createPlayer(std::string texPath, Vector2D pos, int boundX, int boundY) {
	player = new Entity(this);
	Texture* txtFrog = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/ranaSpritesheet.png", 4, 4);
	Texture* txtTongue = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/spritesheetTongue.png", 3, 1);

	AnimationComponent* rndr = new RenderComponentFrog(txtFrog, txtTongue);
	rndr->setContext(player);

	Animation a; //Animaciones de la rana
	a = Animation({ Vector2D(0,0), Vector2D(0,1) }, false, false);
	rndr->addAnimation("DOWN", a);
	a = Animation({ Vector2D(1,0), Vector2D(1,1) }, false, false);
	rndr->addAnimation("UP", a);
	a = Animation({ Vector2D(2,0), Vector2D(2,1) }, false, false);
	rndr->addAnimation("RIGHT", a);
	a = Animation({ Vector2D(2,0), Vector2D(2,1) }, true, false);
	rndr->addAnimation("LEFT", a);

	a = Animation({ Vector2D(2,0), Vector2D(2,2),Vector2D(2,2), Vector2D(2,3) }, false, false);
	rndr->addAnimation("ATTACK_RIGHT", a);
	a = Animation({ Vector2D(2,0), Vector2D(2,2),Vector2D(2,2), Vector2D(2,3) }, true, false);
	rndr->addAnimation("ATTACK_LEFT", a);
	a = Animation({ Vector2D(1,0),Vector2D(1,2),Vector2D(1,2) , Vector2D(1,3) }, false, false);
	rndr->addAnimation("ATTACK_UP", a);
	a = Animation({ Vector2D(0,0),Vector2D(0,2),Vector2D(0,2), Vector2D(0,3) }, false, false);
	rndr->addAnimation("ATTACK_DOWN", a);
	player->addAnimationComponent(rndr);

	//AnimationComponent* anim = new AnimationComponent(txtFrog, 4, 4);
	//player->addComponent(ANIMATION_COMPONENT, anim);
	//anim->setContext(player);

	MovementComponent* mvm = new MovementComponentFrog(Vector2D(2, 2), rndr);
	mvm->setContext(player);
	mvm->setBoundX(boundX);
	mvm->setBoundY(boundY);
	player->addComponent(MOVEMENT_COMPONENT, mvm);

	//player->addRenderComponent(rndr);

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
	for (auto it = entityList.begin(); it != entityList.end(); ++it) {
		delete* it;
	}
	delete cameraManager;
}
