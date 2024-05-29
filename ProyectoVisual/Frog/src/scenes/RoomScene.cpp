#pragma once
#include "RoomScene.h"
#include "../components/CrazyFrogIAComponent.h"
#include "../components/MovementComponentFly.h"
#include "../components/RenderComponent.h"
#include "../components/RenderComponentFrog.h"
#include "../components/RenderComponentSnake.h"
#include "../components/AttackComponentFrog.h"
#include "../components/AttackComponentSnake.h"
#include "../components/MovementComponentFrog.h"
#include "../components/FollowPlayerComponent.h"
#include "../components/AnimationComponent.h"
#include "../components/MovementComponentFish.h";
#include "../components/MovementComponentBlackAnt.h";
#include "../components/MovementComponentRedAnt.h"
#include "../components/MovementComponentSnake.h"
#include "../components/BossComponent.h"
#include "../components/FrogInputComponent.h"
#include "../components/ColliderComponent.h"
#include "../components/MovementComponentFrancois.h"
#include "../components/MovementComponentBomb.h"
#include "../components/LifeComponent.h"
#include "../components/CogibleObjectComponent.h"
#include "../sdlutils/Texture.h"
#include "../components/AddTermiteComponent.h"

void RoomScene::render() {
	mapReader->draw(sdlutils().renderer());

	for (Entity* e : entityList) {
		if (e != nullptr)
			e->render();
	}
	if(francois != nullptr) static_cast<BossComponent*>(francois->getComponent(BOSS_COMPONENT))->render();
	HUD->render();
	if (insideShop) shopManager->render();
}

void RoomScene::update() {
	//para poder añadir elementos en ejecución
	for (int i = 0; i < entityList.size(); i++)
	{
		if (entityList[i] != nullptr)
			entityList[i]->update();

	}

	HUD->update();
	cameraManager->update();
	if (insideShop) {
		shopManager->update();
	}

	if (needMapChange)
		changeMap();
	//comrpueba las colisiones con la rana
	CheckColisions();

	if (francois != nullptr && static_cast<BossComponent*>(francois->getComponent(BOSS_COMPONENT))->theresCutleryToAdd())
		static_cast<BossComponent*>(francois->getComponent(BOSS_COMPONENT))->addCutlery();
}

void RoomScene::CheckColisions() {
	for (Entity* e1 : entityList) {
		ColliderComponent* coll1 = static_cast<ColliderComponent*>(e1->getComponent(COLLIDER_COMPONENT));
		if (coll1 != nullptr) {
			for (Entity* e2 : entityList) {
				coll1->CheckCollision(e2);
			}
		}
	}
}

void RoomScene::callForMapChange(std::string nextMap, flonkOrig nextFlonk)
{
	this->nextMap = nextMap; this->nextFlonk = nextFlonk;  needMapChange = true;
}

Entity* RoomScene::createPlayer(Vector2D pos, int boundX, int boundY)
{
	player = new Entity(this, FROG_ENTITY);

	Texture* txtFrog = &sdlutils().images().at("frogSheet");
	Texture* txtTongue = &sdlutils().images().at("TongueSheet");

	TransformComponent* transform = new TransformComponent(pos);
	player->addComponent(TRANSFORM_COMPONENT, transform);

	ColliderComponent* collider = new ColliderComponent(transform);
	player->addComponent(COLLIDER_COMPONENT, collider);

	AnimationComponent* animFrog = new AnimationComponent();
	RenderComponentFrog* renderFrog = new RenderComponentFrog(txtFrog, txtTongue, animFrog);
	player->addRenderComponentFrog(renderFrog);


	animFrog->addAnimation("IDLE_DOWN", Animation({ Vector2D(0,0) }, false,false, false));
	animFrog->addAnimation("IDLE_UP", Animation({ Vector2D(1,0) }, false, false, false));
	animFrog->addAnimation("IDLE_RIGHT",Animation({ Vector2D(2,0) }, false, false, false));
	animFrog->addAnimation("IDLE_LEFT", Animation({ Vector2D(2,0) }, true, false, false));

	animFrog->addAnimation("DOWN", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, false, false));
	animFrog->addAnimation("UP", Animation({ Vector2D(1,0), Vector2D(1,1) }, false, false, false));
	animFrog->addAnimation("RIGHT", Animation({ Vector2D(2,0), Vector2D(2,1) }, false, false, false));
	animFrog->addAnimation("LEFT", Animation({ Vector2D(2,0), Vector2D(2,1) }, true, false, false));

	animFrog->addAnimation("ATTACK_RIGHT", Animation({ Vector2D(2,2) }, false, false, false));
	animFrog->addAnimation("ATTACK_LEFT", Animation({ Vector2D(2,2) }, true, false, false));
	animFrog->addAnimation("ATTACK_UP", Animation({ Vector2D(1,2) }, false, false, false));
	animFrog->addAnimation("ATTACK_DOWN", Animation({ Vector2D(0,2) }, false, false, false));

	animFrog->addAnimation("DAMAGE", Animation({ Vector2D(3,0) }, false, false, false));

	player->addComponent(ANIMATION_COMPONENT, animFrog);

	MovementComponentFrog* mvm = new MovementComponentFrog(pos, animFrog);
	player->addComponent(MOVEMENT_COMPONENT, mvm);

	AttackComponentFrog* atck = new AttackComponentFrog();
	player->addComponent(ATTACK_COMPONENT, atck);

	InventoryComponent* invComp = new InventoryComponent();
	player->addComponent(INVENTORY_COMPONENT, invComp);

	ItemThrowerComponent* it = new ItemThrowerComponent();
	player->addComponent(ITEM_THROWER_COMPONENT, it);

	FrogInputComponent* input = new FrogInputComponent();
	input->setComponents(mvm, atck, invComp, it);
	player->addComponent(INPUT_COMPONENT, input);

	DamageBehaviourComponent* dam = new DamageBehaviourComponent("DAMAGE");
	player->addComponent(DAMAGE_COMPONENT, dam);

	LifeComponent* lc = new LifeComponent(10, 10);
	player->addComponent(LIFE_COMPONENT, lc);

	//Accedemos al Singleton del HUD para enlazar las vidas del jugador con el HUD
	HUDManager::instance()->LinkLives(lc);

	AddEntity(player);

	return player;
}

Entity* RoomScene::createTransition(Vector2D pos, std::string objName, std::string nextMap) {
	Entity* c = new Entity(this);

	TransformComponent* transform = nullptr;

	flonkOrig nextFlonk;
	if (objName == "TransitionT") {
		nextFlonk = T;

		if (insideShop) {
			transform = new TransformComponent(pos);
			c->addComponent(TRANSFORM_COMPONENT, transform);
		}
		else {
			pos.setX(pos.getX() - 4);
			pos.setY(pos.getY() - 3);
			transform = new TransformComponent(pos, 320, 260);
			c->addComponent(TRANSFORM_COMPONENT, transform);
			Texture* textTienda = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/Arbol_exterior.png", 1, 1);
			RenderComponent* renderTienda = new RenderComponent(textTienda);
			//c->addComponent(RENDER_COMPONENT, renderTienda);
			c->addRenderComponent(renderTienda);
		}
	}
	else {
		transform = new TransformComponent(pos);
		c->addComponent(TRANSFORM_COMPONENT, transform);

		if (objName == "TransitionN") {
			nextFlonk = S;
		}
		else if (objName == "TransitionS") {
			nextFlonk = N;
		}
		else if (objName == "TransitionE") {
			nextFlonk = W;
		}
		else if (objName == "TransitionW") {
			nextFlonk = E;
		}
		else if (objName == "TransitionP") {
			nextFlonk = P;
		}
		else {
			nextFlonk = S;
		}
	}

	ColliderComponent* colliderComp = new ColliderComponent(transform);
	c->addComponent(COLLIDER_COMPONENT, colliderComp);

	TransitionComponent* trans = new TransitionComponent(nextMap, nextFlonk);
	c->addComponent(TRANSITION_COMPONENT, trans);

	AddEntity(c);

	return c;
}

//Objetos tales como las monedas, mejoras y power ups
Entity* RoomScene::createCogible(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps) {
	Entity* c = new Entity(this, COGIBLE_ENTITY);

	//Configura primero comportamiento de objeto cogible general.
	TransformComponent* transform = new TransformComponent(pos);
	c->addComponent(TRANSFORM_COMPONENT, transform);
	
	ColliderComponent* collider = new ColliderComponent(transform);
	c->addComponent(COLLIDER_COMPONENT, collider);

	//Agrega componente que define el comportamiento específico de ese objeto cogible a través
	//De un switch (parece que para c++ no hay switch con strings).
	if (objName == "Gancho") {
		Texture* texture = &sdlutils().images().at("hook");
		RenderComponent* render = new RenderComponent(texture);
		c->addRenderComponent(render);

		CogibleObjectComponent* cogible = new CogibleObjectComponent(GANCHO);
		c->addComponent(COGIBLE_OBJECT_COMPONENT, cogible);
	} 
	else if (objName == "BolsaBombas") {
		Texture* texture = &sdlutils().images().at("bag");
		RenderComponent* render = new RenderComponent(texture);
		c->addRenderComponent(render);

		CogibleObjectComponent* cogible = new CogibleObjectComponent(SACO_BOMBAS);
		c->addComponent(COGIBLE_OBJECT_COMPONENT, cogible);
	}
	else if (objName == "Mosca") { //Revisar como se llama en el mapa
		Texture* texture = &sdlutils().images().at("fly");
		RenderComponent* render = new RenderComponent(texture);
		c->addRenderComponent(render);

		CogibleObjectComponent* cogible = new CogibleObjectComponent(MOSCAS);
		c->addComponent(COGIBLE_OBJECT_COMPONENT, cogible);
	}
	else if (objName == "Orbe") { //Revisar como se llama en el mapa
		Texture* texture = &sdlutils().images().at("orbeOff");
		RenderComponent* render = new RenderComponent(texture);
		c->addRenderComponent(render);

		CogibleObjectComponent* cogible = new CogibleObjectComponent(ORBES);
		c->addComponent(COGIBLE_OBJECT_COMPONENT, cogible);
	}
	else if (objName == "LLave") {
		Texture* texture = &sdlutils().images().at("llave");
		RenderComponent* render = new RenderComponent(texture);
		c->addRenderComponent(render);

		CogibleObjectComponent* cogible = new CogibleObjectComponent(LLAVES);
		c->addComponent(COGIBLE_OBJECT_COMPONENT, cogible);
	}
	// else 	if (objName == "BolsaBombas") { //Revisar como se llama en el mapa
	// Texture* texture = &sdlutils().images().at("bag");
	// RenderComponent* render = new RenderComponent(texture);
	// c->addRenderComponent(render);

	// CogibleObjectComponent* cogible = new CogibleObjectComponent(SACO_BOMBAS);
	// c->addComponent(COGIBLE_OBJECT_COMPONENT, cogible);
	//}

	AddEntity(c);

	return c;
}

Entity* RoomScene::createMoneda(Vector2D pos, MonedaType type) {
	Entity* c = new Entity(this, COGIBLE_ENTITY);

	TransformComponent* transform = new TransformComponent(pos);
	c->addComponent(TRANSFORM_COMPONENT, transform);

	Texture* txtMoneda;
	//Selecciona la textura correcta para la moneda
	switch (type) {
	case MONEDA_ROSA:
		txtMoneda = &sdlutils().images().at("wormPinkSheet");
		break;
	case MONEDA_MORADO:
		txtMoneda = &sdlutils().images().at("wormPurpleSheet");
		break;
	case MONEDA_NARANJA:
		txtMoneda = &sdlutils().images().at("wormGoldSheet");
		break;
	default: //Default por si el tipo se asignó mal
		txtMoneda = &sdlutils().images().at("wormPinkSheet");
		cerr << "identificador de moneda invalido, default";
		break;
	}

	AnimationComponent* ac = new AnimationComponent();
	ac->addAnimation("ANIM", Animation({ Vector2D(0,0), Vector2D(0,1)}, false, false, true));
	c->addComponent(ANIMATION_COMPONENT, ac);
	ac->playAnimation("ANIM");

	RenderComponent* renderMoneda = new RenderComponent(txtMoneda);
	c->addRenderComponent(renderMoneda);

	ColliderComponent* collider = new ColliderComponent(transform);
	c->addComponent(COLLIDER_COMPONENT, collider);

	CogibleObjectComponent* cogible = new CogibleObjectComponent(MONEDAS, type);
	c->addComponent(COGIBLE_OBJECT_COMPONENT, cogible);

	AddEntity(c);

	return c;
}

Entity* RoomScene::createLifeFly(Vector2D pos) {
	Entity* c = new Entity(this, COGIBLE_ENTITY);

	TransformComponent* transform = new TransformComponent(pos);
	c->addComponent(TRANSFORM_COMPONENT, transform);

	Texture* txtMosca = &sdlutils().images().at("flySheet");

	AnimationComponent* ac = new AnimationComponent();
	ac->addAnimation("ANIM", Animation({ Vector2D(0,0), Vector2D(0,2) }, false, false, true));
	c->addComponent(ANIMATION_COMPONENT, ac);
	ac->playAnimation("ANIM");

	RenderComponent* renderMosca = new RenderComponent(txtMosca);
	c->addRenderComponent(renderMosca);

	ColliderComponent* collider = new ColliderComponent(transform);
	c->addComponent(COLLIDER_COMPONENT, collider);

	CogibleObjectComponent* cogible = new CogibleObjectComponent(MOSCAS);
	c->addComponent(COGIBLE_OBJECT_COMPONENT, cogible);

	AddEntity(c);
	return c;
}

/*Metodo que sirve para revivir a Flonk en caso de que pierda todas sus vidas.
  Se invoca dando a reintentar en la pantalla de Game Over. */
void RoomScene::revivePlayer() {
	std::cout << "Player revivido" << std::endl;
	// Reseteamos sus vidas
	LifeComponent* lf = static_cast<LifeComponent*>(player->getComponent(LIFE_COMPONENT));
	lf->AddActual(lf->GetMax()); 
	lf->resetTimer();
	DamageBehaviourComponent* dm = static_cast<DamageBehaviourComponent*>(player->getComponent(DAMAGE_COMPONENT));
	dm->setDead(false);

	//Reproducimos animacion inicial
	AnimationComponent* anim = static_cast<AnimationComponent*>(player->getComponent(ANIMATION_COMPONENT));
	anim->playAnimation("IDLE_DOWN");

	//movemos a Flonk a su ultima posicion de spawn
	movePlayer(lastFrogPosition);

	//movemos la camara hasta la nueva posicion de Flonk
	cameraManager->setTarget(player);

	HUD->update();

	gameOver = false; //reseteamos el booleano que indica el fin de partida
}

Entity* RoomScene::createCrazyFrog(Vector2D pos)
{
	Entity* frog = new Entity(this, CRAZY_FROG_ENTITY);

	Texture* txtFrog = &sdlutils().images().at("crazyFrogSheet");
	Texture* txtTongue = &sdlutils().images().at("TongueSheet");

	TransformComponent* transform = new TransformComponent(pos);
	frog->addComponent(TRANSFORM_COMPONENT, transform);

	Box* boxCrazyFrog = new Box(pos);
	Collider coll = Collider(boxCrazyFrog);

	ColliderComponent* collider = new ColliderComponent(transform);
	collider->AddCollider(coll);
	frog->addComponent(COLLIDER_COMPONENT, collider);

	AnimationComponent* animFrog = new AnimationComponent();
	RenderComponentFrog* renderFrog = new RenderComponentFrog(txtFrog, txtTongue, animFrog);

	animFrog->addAnimation("IDLE_DOWN", Animation({ Vector2D(0,0) }, false, false, false));
	animFrog->addAnimation("IDLE_UP", Animation({ Vector2D(1,0) }, false, false, false));
	animFrog->addAnimation("IDLE_RIGHT", Animation({ Vector2D(2,0) }, false, false, false));
	animFrog->addAnimation("IDLE_LEFT", Animation({ Vector2D(2,0) }, true, false, false));

	animFrog->addAnimation("DOWN", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, false, false));
	animFrog->addAnimation("UP", Animation({ Vector2D(1,0), Vector2D(1,1) }, false, false, false));
	animFrog->addAnimation("RIGHT", Animation({ Vector2D(2,0), Vector2D(2,1) }, false, false, false));
	animFrog->addAnimation("LEFT", Animation({ Vector2D(2,0), Vector2D(2,1) }, true, false, false));

	animFrog->addAnimation("ATTACK_RIGHT", Animation({ Vector2D(2,2) }, false, false, false));
	animFrog->addAnimation("ATTACK_LEFT", Animation({ Vector2D(2,2) }, true, false, false));
	animFrog->addAnimation("ATTACK_UP", Animation({ Vector2D(1,2) }, false, false, false));
	animFrog->addAnimation("ATTACK_DOWN", Animation({ Vector2D(0,2) }, false, false, false));

	animFrog->addAnimation("DAMAGE", Animation({ Vector2D(3,0) }, false, false, false));


	frog->addRenderComponentFrog(renderFrog);
	frog->addComponent(ANIMATION_COMPONENT, animFrog);

	MovementComponentFrog* mvm = new MovementComponentFrog(pos, animFrog);
	frog->addComponent(MOVEMENT_COMPONENT, mvm);

	AttackComponentFrog* atck = new AttackComponentFrog();
	frog->addComponent(ATTACK_COMPONENT, atck);

	CrazyFrogIAComponent* IA = new CrazyFrogIAComponent(mvm, atck);
	frog->addComponent(IACOMPONENT, IA);

	DamageBehaviourComponent* dm = new DamageBehaviourComponent("DAMAGE");
	frog->addComponent(DAMAGE_COMPONENT, dm);

	LifeComponent* lf = new LifeComponent(2, 2);
	frog->addComponent(LIFE_COMPONENT, lf);

	AddEntity(frog);
	return frog;
}
Entity* RoomScene::createFish(Vector2D pos, int boundX) {
	Entity* fish = new Entity(this, FISH_ENTITY);
	Texture* txtFish = &sdlutils().images().at("fishSheet");

	TransformComponent* transform = new TransformComponent(pos);
	fish->addComponent(TRANSFORM_COMPONENT, transform);
	Box* boxFish = new Box(pos);
	Collider coll = Collider(boxFish);
	ColliderComponent* collider = new ColliderComponent(transform);
	collider->AddCollider(coll);
	fish->addComponent(COLLIDER_COMPONENT, collider);
	AnimationComponent* animFish = new AnimationComponent();
	animFish->addAnimation("RIGHT", Animation({ Vector2D(0,1), Vector2D(0,2) }, true, false, false));
	animFish->addAnimation("LEFT", Animation({ Vector2D(0,1), Vector2D(0,2) }, false, false, false));
	animFish->addAnimation("JUMP_RIGHT", Animation({ Vector2D(0,0) }, true, false, false));
	animFish->addAnimation("JUMP_LEFT", Animation({ Vector2D(0,0) }, false, false, false));
	fish->addComponent(ANIMATION_COMPONENT, animFish);

	RenderComponent* renderFish = new RenderComponent(txtFish);
	fish->addRenderComponent(renderFish);

	//el limite tiene que ser una propiedad
	MovementComponentFish* mvm = new MovementComponentFish(boundX, animFish);
	fish->addComponent(MOVEMENT_COMPONENT, mvm);
	AttackComponentBasicEnemy* attack = new AttackComponentBasicEnemy(1);
	fish->addComponent(ATTACK_COMPONENT, attack);


	DamageBehaviourComponent* dm = new DamageBehaviourComponent(""); //El pez no tiene animación de ataque
	fish->addComponent(DAMAGE_COMPONENT, dm);

	LifeComponent* lf = new LifeComponent(2, 2);
	fish->addComponent(LIFE_COMPONENT, lf);

	AddEntity(fish);
	return fish;	
}
Entity* RoomScene::createBlackAnt(Vector2D pos, MovementComponentFrog* playerMvmCmp) {
	Entity* blackAnt = new Entity(this, BLACK_ANT_ENTITY);
	Texture* txtBlackAnt = &sdlutils().images().at("blackAntSheet");

	TransformComponent* transform = new TransformComponent(pos);
	blackAnt->addComponent(TRANSFORM_COMPONENT, transform);
	Box* boxBlackAnt = new Box(pos);
	Collider coll = Collider(boxBlackAnt);
	ColliderComponent* collider = new ColliderComponent(transform);
	collider->AddCollider(coll);
	blackAnt->addComponent(COLLIDER_COMPONENT, collider);
	AnimationComponent* animBlackAnt = new AnimationComponent();
	animBlackAnt->setContext(blackAnt);
	animBlackAnt->addAnimation("UP", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, false, false));
	animBlackAnt->addAnimation("DOWN", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, true, false));
	animBlackAnt->addAnimation("RIGHT", Animation({ Vector2D(1,0), Vector2D(1,1) }, false, false, false));
	animBlackAnt->addAnimation("LEFT", Animation({ Vector2D(1,0), Vector2D(1,1) }, true, false, false));

	animBlackAnt->addAnimation("DAMAGE", Animation({ Vector2D(2,0) }, false, false, false));
	
	blackAnt->addComponent(ANIMATION_COMPONENT, animBlackAnt);

	RenderComponent* renderBlackAnt = new RenderComponent(txtBlackAnt);
	blackAnt->addRenderComponent(renderBlackAnt);
	
	MovementComponentBlackAnt* mvm = new MovementComponentBlackAnt(animBlackAnt);
	blackAnt->addComponent(MOVEMENT_COMPONENT, mvm);

	AttackComponentBasicEnemy* attack = new AttackComponentBasicEnemy(4);
	blackAnt->addComponent(ATTACK_COMPONENT, attack);

	DamageBehaviourComponent* dm = new DamageBehaviourComponent("DAMAGE");
	blackAnt->addComponent(DAMAGE_COMPONENT, dm);

	LifeComponent* lf = new LifeComponent(6, 6);
	blackAnt->addComponent(LIFE_COMPONENT, lf);

	AddEntity(blackAnt);
	return blackAnt;
}

Entity* RoomScene::createRedAnt(Vector2D pos, MovementComponentFrog* playerMvmCmp) {
	Entity* redAnt = new Entity(this,RED_ANT_ENTITY);
	//textura cambiar
	Texture* txtRedAnt = &sdlutils().images().at("redAntSheet");

	TransformComponent* transform = new TransformComponent(pos);
	redAnt->addComponent(TRANSFORM_COMPONENT, transform);
	Box* boxRedAnt = new Box(pos);
	Collider coll = Collider(boxRedAnt);
	ColliderComponent* collider = new ColliderComponent(transform);
	collider->AddCollider(coll);
	redAnt->addComponent(COLLIDER_COMPONENT, collider);
	AnimationComponent* animRedAnt = new AnimationComponent();
	animRedAnt->setContext(redAnt);
	animRedAnt->addAnimation("UP", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, false, false));
	animRedAnt->addAnimation("DOWN", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, true, false));
	animRedAnt->addAnimation("RIGHT", Animation({ Vector2D(1,0), Vector2D(1,1) }, false, false, false));
	animRedAnt->addAnimation("LEFT", Animation({ Vector2D(1,0), Vector2D(1,1) }, true, false, false));
	animRedAnt->addAnimation("DEAD", Animation({ Vector2D(3,0), Vector2D(3,0) }, false, false, false));
	redAnt->addComponent(ANIMATION_COMPONENT, animRedAnt);

	RenderComponent* renderRedAnt = new RenderComponent(txtRedAnt);
	redAnt->addRenderComponent(renderRedAnt);

	MovementComponentRedAnt* mvm = new MovementComponentRedAnt(animRedAnt, playerMvmCmp);
	redAnt->addComponent(MOVEMENT_COMPONENT, mvm);

	AttackComponentBasicEnemy* attack = new AttackComponentBasicEnemy(1);
	redAnt->addComponent(ATTACK_COMPONENT, attack);

	SwallowComponent* swall = new SwallowComponent();
	redAnt->addComponent(SWALLOW_COMPONENT, swall);

	AddEntity(redAnt);
	return redAnt;
}
Entity* RoomScene::createHeadCockroach(Vector2D pos, bool move) {
	Entity* head = new Entity(this, COGIBLE_ENTITY);
	TransformComponent* transform = new TransformComponent(pos);
	head->addComponent(TRANSFORM_COMPONENT, transform);

	ColliderComponent* collider = new ColliderComponent(transform);
	head->addComponent(COLLIDER_COMPONENT, collider);
	Texture* texture = &sdlutils().images().at("roachHead");
	RenderComponent* render = new RenderComponent(texture);
	head->addRenderComponent(render);

	CogibleObjectComponent* cogible = new CogibleObjectComponent(ROACH_HEAD);
	head->addComponent(COGIBLE_OBJECT_COMPONENT, cogible);

	MovementComponentHeadRoach* mvm = new MovementComponentHeadRoach(move);
	head->addComponent(MOVEMENT_COMPONENT, mvm);
	AddEntity(head);
	return head;
}

Entity* RoomScene::createCockroach(Vector2D pos) {
	Entity* cockroach = new Entity(this, COCKROACH_ENTITY);
	//textura cambiar
	Texture* txtcockroach = &sdlutils().images().at("roachSheet");//supongo que esto estaba de placeholder

	TransformComponent* transform = new TransformComponent(pos);
	cockroach->addComponent(TRANSFORM_COMPONENT, transform);
	Box* boxCockroach = new Box(pos);
	Collider coll = Collider(boxCockroach);
	ColliderComponent* collider = new ColliderComponent(transform);
	collider->AddCollider(coll);
	cockroach->addComponent(COLLIDER_COMPONENT, collider);
	AnimationComponent* animcockroach = new AnimationComponent();
	animcockroach->setContext(cockroach);
	animcockroach->addAnimation("UP", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, false, false));
	animcockroach->addAnimation("DOWN", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, true, false));
	animcockroach->addAnimation("RIGHT", Animation({ Vector2D(1,0), Vector2D(1,1) }, false, false, false));
	animcockroach->addAnimation("LEFT", Animation({ Vector2D(1,0), Vector2D(1,1) }, true, false, false));
	animcockroach->addAnimation("DAMAGE", Animation({ Vector2D(2,0), Vector2D(2,0) }, false, false, false));

	cockroach->addComponent(ANIMATION_COMPONENT, animcockroach);

	RenderComponent* renderanimcockroach = new RenderComponent(txtcockroach);
	cockroach->addRenderComponent(renderanimcockroach);

	MovementComponentCockroach* mvm = new MovementComponentCockroach(animcockroach);
	cockroach->addComponent(MOVEMENT_COMPONENT, mvm);
	AttackComponentBasicEnemy* attack = new AttackComponentBasicEnemy(1);
	cockroach->addComponent(ATTACK_COMPONENT, attack);
	DamageBehaviourComponent* dm = new DamageBehaviourComponent("DAMAGE");
	cockroach->addComponent(DAMAGE_COMPONENT, dm);
	LifeComponent* lc = new LifeComponent(2, 2);
	cockroach->addComponent(LIFE_COMPONENT, lc);
	AddEntity(cockroach);
	return cockroach;
}
Entity* RoomScene::createExplotableDoor(Vector2D pos) {
	Entity* door = new Entity(this, EXPLOITABLE_ENTITY);
	//Texture* txtDoor = &sdlutils().images().at("fishSheet"); falta definir la textura verdadera de la puerta
	Texture* txtDoor = &sdlutils().images().at("fishSheet");

	TransformComponent* transform = new TransformComponent(pos);
	door->addComponent(TRANSFORM_COMPONENT, transform);

	ColliderComponent* collider = new ColliderComponent(transform);
	door->addComponent(COLLIDER_COMPONENT, collider);

	AnimationComponent* animDoor = new AnimationComponent();
	animDoor->setContext(door);
	animDoor->addAnimation("IDLE", Animation({ Vector2D(0,1) }, true, false, false));
	animDoor->addAnimation("DEATH", Animation({ Vector2D(0,0) }, false, false, true));
	door->addComponent(ANIMATION_COMPONENT, animDoor);
	animDoor->playAnimation("IDLE"); //Al crear la puerta esta en modo idle

	RenderComponent* renderDoor = new RenderComponent(txtDoor);
	door->addRenderComponent(renderDoor);

	ExploitableComponent* exp = new ExploitableComponent();
	door->addComponent(EXPLOITABLE_COMPONENT, exp);

	AddEntity(door);
	return door;
}
Entity* RoomScene::createSnake(Vector2D pos) {
	Entity* snake = new Entity(this, SNAKE_ENTITY);
	Texture* txtSnake = &sdlutils().images().at("snakeSheet");
	Texture* txtNeck = &sdlutils().images().at("snakeAttackSheet");

	TransformComponent* transform = new TransformComponent(pos);
	snake->addComponent(TRANSFORM_COMPONENT, transform);

	Box* boxSnake = new Box(pos);
	Collider coll = Collider(boxSnake);
	ColliderComponent* collider = new ColliderComponent(transform);
	collider->AddCollider(coll);
	snake->addComponent(COLLIDER_COMPONENT, collider);

	AnimationComponent* animSnake = new AnimationComponent();
	snake->addComponent(ANIMATION_COMPONENT, animSnake);

	animSnake->addAnimation("IDLE_RIGHT", Animation({ Vector2D(2,0) }, false, false, false));
	animSnake->addAnimation("IDLE_LEFT", Animation({ Vector2D(2,0) }, true, false, false));
	animSnake->addAnimation("IDLE_DOWN", Animation({ Vector2D(1,0) }, false, false, false));
	animSnake->addAnimation("IDLE_UP", Animation({ Vector2D(0,0) }, false, false, false));
	animSnake->addAnimation("ATTACK_RIGHT", Animation({ Vector2D(2,1) }, false, false, false));
	animSnake->addAnimation("ATTACK_LEFT", Animation({ Vector2D(2,1) }, true, false, false));
	animSnake->addAnimation("ATTACK_DOWN", Animation({ Vector2D(1,1) }, false, false, false));
	animSnake->addAnimation("ATTACK_UP", Animation({ Vector2D(0,1) }, false, false, false));

	animSnake->addAnimation("DAMAGE", Animation({ Vector2D(3,0) }, false, false, false));


	RenderComponentSnake* renderSnake = new RenderComponentSnake(txtSnake, txtNeck, animSnake);
	snake->addRenderComponentSnake(renderSnake);

	MovementComponentSnake* mvmSnake = new MovementComponentSnake(animSnake);
	snake->addComponent(MOVEMENT_COMPONENT, mvmSnake);

	AttackComponentSnake* atckSnake = new AttackComponentSnake();
	snake->addComponent(ATTACK_COMPONENT, atckSnake);

	DamageBehaviourComponent* dm = new DamageBehaviourComponent("DAMAGE");
	snake->addComponent(DAMAGE_COMPONENT, dm);

	LifeComponent* lfSnake = new LifeComponent(6, 6);
	snake->addComponent(LIFE_COMPONENT, lfSnake);

	AddEntity(snake);
	return snake;
}

Entity* RoomScene::createFrancois()
{
	francois = new Entity(this,FRENCH_ENTITY);

	Texture* txtFran = &sdlutils().images().at("darkShadow");

	TransformComponent* tr = new TransformComponent(Vector2D(15, 0), BOSS_X, BOSS_Y, BOSS_SCALE);
	francois->addComponent(TRANSFORM_COMPONENT, tr);

	RenderComponent* renderTheFrench = new RenderComponent(txtFran);
	francois->addRenderComponent(renderTheFrench);

	ColliderComponent* bossColl = new ColliderComponent(tr);
	francois->addComponent(COLLIDER_COMPONENT, bossColl);

	MovementComponentFrancois* move = new MovementComponentFrancois();
	francois->addComponent(MOVEMENT_COMPONENT, move);

	BossComponent* bossComp = new BossComponent();
	francois->addComponent(BOSS_COMPONENT, bossComp);

	AddEntity(francois);
	
	return francois;
}

Entity* RoomScene::createBomb(Vector2D pos) {
	Entity* bomb = new Entity(this, BOMB_ENTITY);
	Texture* textBomb = &sdlutils().images().at("eggSheet");

	TransformComponent* transform = new TransformComponent(pos,TILE_SIZE,TILE_SIZE);
	bomb->addComponent(TRANSFORM_COMPONENT, transform);

	AnimationComponent* animBomb = new AnimationComponent();
	animBomb->addAnimation("BOMB_IDLE", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, false, true));
	bomb->addComponent(ANIMATION_COMPONENT, animBomb);

	RenderComponent* renderBomb = new RenderComponent(textBomb);
	bomb->addRenderComponent(renderBomb);


	ColliderComponent* collBomb = new ColliderComponent(transform);
	bomb->addComponent(COLLIDER_COMPONENT, collBomb);

	MovementComponentBomb* moveBomb = new MovementComponentBomb();
	bomb->addComponent(MOVEMENT_COMPONENT, moveBomb);

	AddEntity(bomb);
	return bomb;
}
Entity* RoomScene::createPiedraMovible(Vector2D pos, int objIntID)
{
	Entity* piedra = new Entity(this, PIEDRAMOV_ENTITY);
	Texture* textBomb = &sdlutils().images().at("piedra");

	TransformComponent* transform = new TransformComponent(pos);
	piedra->addComponent(TRANSFORM_COMPONENT, transform);

	RenderComponent* renderPiedra = new RenderComponent(textBomb);
	//piedra->addComponent(RENDER_COMPONENT, renderPiedra);
	piedra->addRenderComponent(renderPiedra);

	//Box* boxPiedra = new Box(pos);
	//Collider coll = Collider(boxPiedra);
	ColliderComponent* collPiedra = new ColliderComponent(transform);
	piedra->addComponent(COLLIDER_COMPONENT, collPiedra);
	
	TonguePushComponent* tongueInteract = new TonguePushComponent(objIntID);
	piedra->addComponent(TONGUEINTERACT_COMPONENT, tongueInteract);	

	AddEntity(piedra);
	return piedra;
}
Entity* RoomScene::createEnganche(Vector2D pos)
{
	Entity* enganche = new Entity(this, ENGANCHE_ENTITY);
	Texture* textEnganche = &sdlutils().images().at("enganche");

	TransformComponent* transform = new TransformComponent(pos);
	enganche->addComponent(TRANSFORM_COMPONENT, transform);

	RenderComponent* renderEnganche = new RenderComponent(textEnganche);
	enganche->addRenderComponent(renderEnganche);

	/*Box* boxEnganche = new Box(pos);
	Collider coll = Collider(boxEnganche);*/
	ColliderComponent* collEnganche = new ColliderComponent(transform);
	enganche->addComponent(COLLIDER_COMPONENT, collEnganche);

	TongueHookComponent* tongueInteract = new TongueHookComponent();
	enganche->addComponent(TONGUEINTERACT_COMPONENT, tongueInteract);

	AddEntity(enganche);
	return enganche;
}
Entity* RoomScene::createMapChanger(string name, Vector2D pos, bool pushed, string nextMap, int objIntID, bool objInteracted)
{
	Entity* e = nullptr;
	Texture* text = nullptr;

	if (name == "Palanca") {
		e =	new Entity(this, PALANCA_ENTITY);
		if (pushed)
			text = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/PalancaA.png", 1, 1);
		else
			text = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/PalancaB.png", 1, 1);
	}
	else if (name == "Boton") {
		e = new Entity(this, BOTON_ENTITY);
		if (!pushed)
			text = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/BotonA.png", 1, 1);
		else
			text = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/BotonB.png", 1, 1);
	}

	TransformComponent* transform = new TransformComponent(pos);
	e->addComponent(TRANSFORM_COMPONENT, transform);
	transform->setContext(e);

	RenderComponent* renderC = new RenderComponent(text);
	renderC->setContext(e);
	renderC->initComponent();
	//e->addComponent(RENDER_COMPONENT, renderC);
	e->addRenderComponent(renderC);

	Box* box = new Box(pos);
	Collider colli = Collider(box);
	ColliderComponent* collC = new ColliderComponent(transform);
	collC->AddCollider(colli);
	collC->setContext(e);
	e->addComponent(COLLIDER_COMPONENT, collC);

	MapShiftComponent* tongueInteract = new MapShiftComponent(nextMap);
	e->addComponent(TONGUEINTERACT_COMPONENT, tongueInteract);
	//tongueInteract->setContext(e);
	//tongueInteract->initComponent();
	

	AddEntity(e);
	return e;
}
Entity* RoomScene::createJarron(Vector2D pos, int loot)
{
	// el loot indica que va a soltar cuando se rompa, 0 = loot aleatorio, 1 = vida y 2 = dinero
	Entity* destructible = new Entity(this, DESTRUCTIBLE_ENTITY);
	Texture* txtDestructible = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/Jarron.png", 1, 1);
	// hay que animarlo

	TransformComponent* transform = new TransformComponent(pos);
	destructible->addComponent(TRANSFORM_COMPONENT, transform);

	RenderComponent* renderDestructible = new RenderComponent(txtDestructible);
	//destructible->addComponent(RENDER_COMPONENT, renderDestructible);
	destructible->addRenderComponent(renderDestructible);

	/*Box* boxdestructible = new Box(pos);
	Collider coll = Collider(boxdestructible);*/
	ColliderComponent* colldestructible = new ColliderComponent(transform);
	destructible->addComponent(COLLIDER_COMPONENT, colldestructible);

	DestructibleComponent* destructibleComponent = new DestructibleComponent(loot, pos);
	destructible->addComponent(DESTRUCTIBLE_COMPONENT, destructibleComponent);

	AddEntity(destructible);
	return destructible;
}
Entity* RoomScene::createDoor(Vector2D pos)
{
	Entity* destructible = new Entity(this, PUERTA_ENTITY);
	Texture* txtDestructible = &sdlutils().images().at("puerta");
	// hay que animarlo

	TransformComponent* transform = new TransformComponent(pos);
	destructible->addComponent(TRANSFORM_COMPONENT, transform);

	RenderComponent* renderDestructible = new RenderComponent(txtDestructible);
	//destructible->addComponent(RENDER_COMPONENT, renderDestructible);
	destructible->addRenderComponent(renderDestructible);

	/*Box* boxdestructible = new Box(pos);
	Collider coll = Collider(boxdestructible)*/;
	ColliderComponent* colldestructible = new ColliderComponent(transform);
	destructible->addComponent(COLLIDER_COMPONENT, colldestructible);

	PuertaComponent* tongueInteract = new PuertaComponent();
	destructible->addComponent(TONGUEINTERACT_COMPONENT, tongueInteract);

	AddEntity(destructible);
	return destructible;
}

Entity* RoomScene::createArbusto(Vector2D pos, int loot)
{
	// el loot indica que va a soltar cuando se rompa, 0 = loot aleatorio, 1 = vida y 2 = dinero
	Entity* destructible = new Entity(this, DESTRUCTIBLE_ENTITY);
	Texture* txtDestructible = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/placeholderArbusto.png", 1, 1);

	TransformComponent* transform = new TransformComponent(pos);
	destructible->addComponent(TRANSFORM_COMPONENT, transform);

	RenderComponent* renderDestructible = new RenderComponent(txtDestructible);
	//destructible->addComponent(RENDER_COMPONENT, renderDestructible);
	destructible->addRenderComponent(renderDestructible);

	//Box* boxdestructible = new Box(pos);
	//Collider coll = Collider(boxdestructible);
	ColliderComponent* colldestructible = new ColliderComponent(transform);
	destructible->addComponent(COLLIDER_COMPONENT, colldestructible);

	DestructibleComponent* destructibleComponent = new DestructibleComponent(loot, pos);
	destructible->addComponent(DESTRUCTIBLE_COMPONENT, destructibleComponent);
	
	AddEntity(destructible);
	return destructible;
}
Entity* RoomScene::createTroncoTermitas(Vector2D pos)
{
	Entity* log = new Entity(this, TERMITELOG_ENTITY);

	TransformComponent* transform = new TransformComponent(pos, 320, 160); //mide dos casillas de ancho, y lo haceis con una constante, asiq numero magico por ahora
	log->addComponent(TRANSFORM_COMPONENT, transform);

	AnimationComponent* anim = new AnimationComponent();
	anim->addAnimation("LOG_IDLE", Animation({ Vector2D(0,0), Vector2D(0,2) }, false, false, true));
	anim->playAnimation("LOG_IDLE");
	log->addComponent(ANIMATION_COMPONENT, anim);

	RenderComponent* renderBomb = new RenderComponent(&sdlutils().images().at("termitaTronco"));
	log->addRenderComponent(renderBomb);

	Box* box = new Box(pos, 320, 160);
	Collider coll = Collider(box);
	ColliderComponent* collider = new ColliderComponent(transform);
	collider->AddCollider(coll);
	log->addComponent(COLLIDER_COMPONENT, collider);

	AttackComponentBasicEnemy* attack = new AttackComponentBasicEnemy(4);
	log->addComponent(ATTACK_COMPONENT, attack); //para q colisione

	AddTermiteComponent* add = new AddTermiteComponent(pos);
	log->addComponent(TERMITE_GENERATOR_COMPONENT, add);

	AddEntity(log);

	return log;
}
Entity* RoomScene::createTermita(Vector2D pos)
{
	Entity* temita = new Entity(this, TERMITE_ENTITY);
	Texture* txt = &sdlutils().images().at("termita");

	TransformComponent* transform = new TransformComponent(pos);
	temita->addComponent(TRANSFORM_COMPONENT, transform);
	Box* box = new Box(pos);
	Collider coll = Collider(box);
	ColliderComponent* collider = new ColliderComponent(transform);
	collider->AddCollider(coll);
	temita->addComponent(COLLIDER_COMPONENT, collider);
	AnimationComponent* anim = new AnimationComponent();
	anim->setContext(temita);
	anim->addAnimation("UP", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, false, false));
	anim->addAnimation("DOWN", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, true, false));
	anim->addAnimation("RIGHT", Animation({ Vector2D(1,0), Vector2D(1,1) }, false, false, false));
	anim->addAnimation("LEFT", Animation({ Vector2D(1,0), Vector2D(1,1) }, true, false, false));
	anim->addAnimation("DEAD", Animation({ Vector2D(3,0), Vector2D(3,0) }, false, false, false));

	temita->addComponent(ANIMATION_COMPONENT, anim);

	RenderComponent* render = new RenderComponent(txt);
	temita->addRenderComponent(render);

	//tiene el mismo comportamiento
	MovementComponentBlackAnt* mvm = new MovementComponentBlackAnt(anim);
	temita->addComponent(MOVEMENT_COMPONENT, mvm);

	AttackComponentBasicEnemy* attack = new AttackComponentBasicEnemy(4);
	temita->addComponent(ATTACK_COMPONENT, attack);

	AddEntity(temita);

	return temita;
}
Entity* RoomScene::createConveyorBelt(Vector2D pos, int rotation)
{
	// rotation: 0 norte, 1 este, 2 sur y 3 oeste
	Entity* conveyor = new Entity(this, CONVEYOR_ENTITY);

	Texture* txtConveyor = nullptr;
	if(rotation == 1 || rotation == 3)
	{
		txtConveyor = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/CintaTransSheetH.png", 1, 1);
	}
	else 
	{
		txtConveyor = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/CintaTransSheetV.png", 1, 1);
	}

		// cambiarlo cuando sea posible

	TransformComponent* transform = new TransformComponent(pos);
	conveyor->addComponent(TRANSFORM_COMPONENT, transform);

	RenderComponent* renderDestructible = new RenderComponent(txtConveyor);
	//conveyor->addComponent(RENDER_COMPONENT, renderDestructible);
	conveyor->addRenderComponent(renderDestructible);

	Box* boxConveyor = new Box(pos);
	Collider coll = Collider(boxConveyor);
	ColliderComponent* collConveyor= new ColliderComponent(transform);
	conveyor->addComponent(COLLIDER_COMPONENT, collConveyor);

	ConveyorBeltComponent* conveyorComponent = new ConveyorBeltComponent(rotation, pos);
	conveyor->addComponent(CONVEYOR_COMPONENT, conveyorComponent);

	AddEntity(conveyor);
	return conveyor;
}
Entity* RoomScene::createEnemy(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps)
{
	Entity* c = nullptr;

	if (objName == "Crazy frog") {
		c = createCrazyFrog(pos);
	}
	else if (objName == "Pez") {
		c = createFish(pos, objProps[0].getIntValue());
	}
	else if (objName == "Black ant") {
		if (player != nullptr) {
			MovementComponentFrog* mvmPlayer = static_cast<MovementComponentFrog*>(player->getComponent(MOVEMENT_COMPONENT));
			c = createBlackAnt(pos, mvmPlayer);
		}
	}
	else if (objName == "Fish") {
		for (const auto& prop : objProps) {
			if (prop.getName() == "object") //revisar esto
			{
				if (prop.getType() == tmx::Property::Type::Int) {
					int boundX = prop.getIntValue();
					c = createFish(pos, boundX);
					//c = createFish(pos, 4);
					break;
				}
			}
		}
	}
	else if (objName == "Red ant") {
		if (player != nullptr) {
			MovementComponentFrog* mvmPlayer = static_cast<MovementComponentFrog*>(player->getComponent(MOVEMENT_COMPONENT));
			c = createRedAnt(pos, mvmPlayer);
		}
	}
	else if (objName == "Snake") {
		c = createSnake(pos);
	}
	else if (objName == "Francois") {
		c = createFrancois();
	}
	else if (objName == "Bomb") {
		c = createBomb(pos);
	}
	else if (objName == "Cockroach") {
		c = createCockroach(pos);
	}
	else if (objName == "Termita") {
		c = createTermita(pos);
	}
	else if (objName == "TermitaTronco") {
		c = createTroncoTermitas(pos);
	}
	return c;
}
Entity* RoomScene::createObjInteract(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps, int objIntID, bool objInteracted)
{
	Entity* c = nullptr;
	
	if (objName == "Jarron")
	{
		c = createJarron(pos, objProps[0].getIntValue());
	}	
	else if (objName == "Arbusto")
	{
		c = createArbusto(pos, objProps[0].getIntValue());
	}
	else if (objName == "PiedraMovible"){
		c = createPiedraMovible(pos, objIntID);
	}	
	else if (objName == "Enganche") {
		c = createEnganche(pos);
	}
	else if (objName == "Palanca" || objName == "Boton") {
		c = createMapChanger(objName, pos, objProps[1].getBoolValue(), objProps[0].getStringValue(), objIntID, objInteracted);
	}
	else if (objName == "CintaTransportadora"){
		c = createConveyorBelt(pos, objProps[0].getIntValue());
	}
	else if (objName == "Puerta"){
		c = createDoor(pos);
	}
	else if (objName == "Recompensa"){
		c = createMoneda(pos, MONEDA_ROSA);
	}

	return c;
}

Entity* RoomScene::createExplotable(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps) {
	Entity* c = nullptr;
	if (objName == "Puerta Explotable") {
		c = createExplotableDoor(pos);
	}
	return c;
}

void RoomScene::resetScene(string path)
{
	auto it = entityList.begin();
	while (it != entityList.end()) {
		//Por la arquitectura actual, es necesario mantener la entidad de frog.
		//Para cada entidad se comprueba su name, si no es un frog lo borra.
		if ((*it)->getName() != FROG_ENTITY) {
			delete* it;
			*it = nullptr;
			it = entityList.erase(it);
		}

		else
			it++;
	}

	revivePlayer();

	if (mapReader != nullptr) {
		mapReader->clearMap();
		mapReader->loadBg(path, sdlutils().renderer());
		mapReader->loadObj(path);

	}

	if (cameraManager != nullptr) {
		cameraManager->setTarget(player);
	}

	TransformComponent* transform = static_cast<TransformComponent*>(player->getComponent(TRANSFORM_COMPONENT));
	if (transform != nullptr) {
		lastFrogPosition = transform->getCasilla();
	}
}

Entity* RoomScene::createEntity(Vector2D pos, std::string objName, std::string objClass, std::vector<tmx::Property> objProps, int objIntID, bool objInteracted)
{
	Entity* c = nullptr;
	
	if (objClass == "Enemigo") {
		c = createEnemy(pos, objName, objProps);
	}
	else if (objClass == "Player") {
		//SOLO CREAR� (aka cambiar� d sitio) EL FLONK QUE CORRESPONDE
		if (player == nullptr) {
			c = createPlayer(pos, 100, 100);
			lastFrogPosition = pos;  //Guardamos ultima posicion de la rana
		}
		else { //FLONK YA EXISTE estamos cambiando de mapa
			bool placeHere = false;
			switch (playerOrig)
			{
			case N:
				if (objName == "FlonkN") placeHere = true;
				break;
			case S:
				if (objName == "FlonkS") placeHere = true;
				break;
			case E:
				if (objName == "FlonkE") placeHere = true;  
				break;
			case W:
				if (objName == "FlonkW") placeHere = true;
				break;
			case P:
				if (objName == "FlonkP") placeHere = true;
				break;
			case T: 
				if (objName == "FlonkT") {
					placeHere = true;
					insideShop = !insideShop;
				}
				break;
			default:
				break;
			}
			if (placeHere) {
				cout << "El flonk q va a aparecer en pantalla es: " << objName << endl;
				movePlayer(pos);
				c = player;
			}
		}
	}

	else if (objClass == "ObjInteract") {
		c = createObjInteract(pos, objName, objProps, objIntID, objInteracted);
	}
	else if (objClass == "Transition") {		
		c = createTransition(pos, objName, objProps[0].getStringValue());
	}
	else if (objClass == "ObjCogible") {
		c = createCogible(pos, objName, objProps);
	}
	else if (objClass == "Explotable") {
		c = createExplotable(pos, objName, objProps);
	}
	return c;
}

void RoomScene::movePlayer(Vector2D pos) {
	static_cast<TransformComponent*>(player->getComponent(TRANSFORM_COMPONENT))->setCasilla(pos);
	if (cameraManager != nullptr)
		cameraManager->setTarget(player);
}

void RoomScene::AddEntity(Entity* entity) {
	entityList.push_back(entity);
}
//Metodo para remover una entidad 
void RoomScene::removeEntity(Entity* entity) {
	auto it = entityList.begin();
	bool eliminated = false;

	while (it != entityList.end() && !eliminated) {
		if (*it == entity) {
			if (*it == player) {
				/*Si es el player->Game Over
				(no borramos a Flonk todavia en caso de que el jugador quiera volver a intentarlo)*/
				gameOver = true; 
			}
			else { //Si es cualquier otra entidad, la borramos
				it = entityList.erase(it);
			}
			eliminated = true;
		}
		else it++;
	}
}
RoomScene::~RoomScene() {

	//Eliminar la lista de entidades
	std::cout << "TOTAL NUMBER OF ENTITIES: " << entityList.size() << std::endl;
	/*for (auto it = entityList.begin(); it != entityList.end(); ++it) {
		delete* it;
	}*/

	for (int i = 0; i < entityList.size(); i++)
	{
		if (entityList[i]->getName() != FRENCH_ENTITY)
		delete entityList[i];
	}

	delete mapReader;
	delete francois;
}

void RoomScene::changeMap()
{
	playerOrig = nextFlonk;

	auto it = entityList.begin();
	while (it != entityList.end()) {
		//Por la arquitectura actual, es necesario mantener la entidad de frog.
		//Para cada entidad se comprueba su name, si no es un frog lo borra.
		if ((*it)->getName() != FROG_ENTITY) {
			delete* it;
			*it = nullptr;
			it = entityList.erase(it);
		}
			
		else
			it++;
	}

	if (mapReader != nullptr) {
		mapReader->clearMap();
		mapReader->loadBg(nextMap, sdlutils().renderer());
		mapReader->loadObj(nextMap);
		if (nextMap == "mapaNF.tmx") createFrancois();
	}
	
	if (cameraManager != nullptr) {
		cameraManager->setTarget(player);
	}
	
	TransformComponent* transform = static_cast<TransformComponent*>(player->getComponent(TRANSFORM_COMPONENT));
	if (transform != nullptr) {
		lastFrogPosition = transform->getCasilla();
	}
	//Actualizamos ultima posición de Spawn de la rana
	

	needMapChange = false;
}
