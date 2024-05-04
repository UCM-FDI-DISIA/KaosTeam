#include "RoomScene.h"
#include "../components/CrazyFrogIAComponent.h"
#include "../components/LifeComponent.h"

void RoomScene::render() {
	mapReader->draw(sdlutils().renderer());

	for (Entity* e : entityList) {
		if (e != nullptr)
			e->render();
	}
	HUD->render();
	if (insideShop) shopManager->render();
}

void RoomScene::update() {
	for (Entity* e : entityList) {
		if (e != nullptr)
			e->update();
	}
	cameraManager->update();
	if (insideShop)
		shopManager->update();
	if (needMapChange)
		changeMap();
	//comrpueba las colisiones con la rana
	CheckColisions();

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


	animFrog->addAnimation("IDLE_DOWN", Animation({ Vector2D(0,0) }, false, false));
	animFrog->addAnimation("IDLE_UP", Animation({ Vector2D(1,0) }, false, false));
	animFrog->addAnimation("IDLE_RIGHT",Animation({ Vector2D(2,0) }, false, false));
	animFrog->addAnimation("IDLE_LEFT", Animation({ Vector2D(2,0) }, true, false));

	animFrog->addAnimation("DOWN", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, false));
	animFrog->addAnimation("UP", Animation({ Vector2D(1,0), Vector2D(1,1) }, false, false));
	animFrog->addAnimation("RIGHT", Animation({ Vector2D(2,0), Vector2D(2,1) }, false, false));
	animFrog->addAnimation("LEFT", Animation({ Vector2D(2,0), Vector2D(2,1) }, true, false));

	animFrog->addAnimation("ATTACK_RIGHT", Animation({ Vector2D(2,2) }, false, false));
	animFrog->addAnimation("ATTACK_LEFT", Animation({ Vector2D(2,2) }, true, false));
	animFrog->addAnimation("ATTACK_UP", Animation({ Vector2D(1,2) }, false, false));
	animFrog->addAnimation("ATTACK_DOWN", Animation({ Vector2D(0,2) }, false, false));

	player->addComponent(ANIMATION_COMPONENT, animFrog);

	MovementComponentFrog* mvm = new MovementComponentFrog(pos, animFrog);
	player->addComponent(MOVEMENT_COMPONENT, mvm);

	AttackComponentFrog* atck = new AttackComponentFrog();
	player->addComponent(ATTACK_COMPONENT, atck);

	InventoryComponent* invComp = new InventoryComponent();
	player->addComponent(INVENTORY_COMPONENT, invComp);

	FrogInputComponent* input = new FrogInputComponent();
	input->setComponents(mvm, atck, invComp);
	player->addComponent(INPUT_COMPONENT, input);

	LifeComponent* lc = new LifeComponent(10, 10);
	player->addComponent(LIFE_COMPONENT, lc);

	MoneyComponent* moneyComp = new MoneyComponent();
	player->addComponent(MONEY_COMPONENT, moneyComp);
	
	AddEntity(player);

	return player;
}

Entity* RoomScene::createTransition(Vector2D pos, std::string objName, std::string nextMap) {
	Entity* c = new Entity(this);

	TransformComponent* transform = new TransformComponent(pos);
	c->addComponent(TRANSFORM_COMPONENT, transform);

	ColliderComponent* colliderComp = new ColliderComponent(transform);
	c->addComponent(COLLIDER_COMPONENT, colliderComp);

	flonkOrig nextFlonk;
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
	else if (objName == "TransitionT") {
		nextFlonk = T;
	}
	else {
		nextFlonk = S;
	}

	TransitionComponent* trans = new TransitionComponent(nextMap, nextFlonk);
	c->addComponent(TRANSITION_COMPONENT, trans);

	AddEntity(c);

	return c;
}

Entity* RoomScene::createCrazyFrog(Vector2D pos)
{
	Entity* frog = new Entity(this, CRAZY_FROG_ENTITY);

	Texture* txtFrog = &sdlutils().images().at("crazyFrogSheet");
	Texture* txtTongue = &sdlutils().images().at("TongueSheet");

	TransformComponent* transform = new TransformComponent(pos);
	frog->addComponent(TRANSFORM_COMPONENT, transform);

	AnimationComponent* animFrog = new AnimationComponent();
	RenderComponentFrog* renderFrog = new RenderComponentFrog(txtFrog, txtTongue, animFrog);

	animFrog->addAnimation("IDLE_DOWN", Animation({ Vector2D(0,0) }, false, false));
	animFrog->addAnimation("IDLE_UP", Animation({ Vector2D(1,0) }, false, false));
	animFrog->addAnimation("IDLE_RIGHT", Animation({ Vector2D(2,0) }, false, false));
	animFrog->addAnimation("IDLE_LEFT", Animation({ Vector2D(2,0) }, true, false));

	animFrog->addAnimation("DOWN", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, false));
	animFrog->addAnimation("UP", Animation({ Vector2D(1,0), Vector2D(1,1) }, false, false));
	animFrog->addAnimation("RIGHT", Animation({ Vector2D(2,0), Vector2D(2,1) }, false, false));
	animFrog->addAnimation("LEFT", Animation({ Vector2D(2,0), Vector2D(2,1) }, true, false));

	animFrog->addAnimation("ATTACK_RIGHT", Animation({ Vector2D(2,2) }, false, false));
	animFrog->addAnimation("ATTACK_LEFT", Animation({ Vector2D(2,2) }, true, false));
	animFrog->addAnimation("ATTACK_UP", Animation({ Vector2D(1,2) }, false, false));
	animFrog->addAnimation("ATTACK_DOWN", Animation({ Vector2D(0,2) }, false, false));

	frog->addRenderComponentFrog(renderFrog);
	frog->addComponent(ANIMATION_COMPONENT, animFrog);

	MovementComponentFrog* mvm = new MovementComponentFrog(pos, animFrog);
	frog->addComponent(MOVEMENT_COMPONENT, mvm);

	AttackComponentFrog* atck = new AttackComponentFrog();
	frog->addComponent(ATTACK_COMPONENT, atck);

	CrazyFrogIAComponent* IA = new CrazyFrogIAComponent(mvm, atck);
	frog->addComponent(IACOMPONENT, IA);

	AddEntity(frog);
	return frog;
}
Entity* RoomScene::createFish(Vector2D pos, int boundX) {
	Entity* fish = new Entity(this, FISH_ENTITY);
	Texture* txtFish = &sdlutils().images().at("fishSheet");

	TransformComponent* transform = new TransformComponent(pos);
	fish->addComponent(TRANSFORM_COMPONENT, transform);

	AnimationComponent* animFish = new AnimationComponent();
	animFish->setContext(fish);
	animFish->addAnimation("RIGHT", Animation({ Vector2D(0,1), Vector2D(0,2) }, true, false));
	animFish->addAnimation("LEFT", Animation({ Vector2D(0,1), Vector2D(0,2) }, false, false));
	animFish->addAnimation("JUMP_RIGHT", Animation({ Vector2D(0,0) }, true, false));
	animFish->addAnimation("JUMP_LEFT", Animation({ Vector2D(0,0) }, false, false));
	fish->addComponent(ANIMATION_COMPONENT, animFish);

	RenderComponent* renderFish = new RenderComponent(txtFish);
	fish->addRenderComponent(renderFish);

	//el limite tiene que ser una propiedad
	MovementComponentFish* mvm = new MovementComponentFish(boundX, animFish);
	fish->addComponent(MOVEMENT_COMPONENT, mvm);

	AddEntity(fish);
	return fish;	
}
Entity* RoomScene::createBlackAnt(Vector2D pos, MovementComponentFrog* playerMvmCmp) {
	Entity* blackAnt = new Entity(this,BLACK_ANT_ENTITY);
	//textura cambiar
	Texture* txtBlackAnt = &sdlutils().images().at("fishSheet");//supongo que esto estaba de placeholder

	TransformComponent* transform = new TransformComponent(pos);
	blackAnt->addComponent(TRANSFORM_COMPONENT, transform);

	AnimationComponent* animBlackAnt = new AnimationComponent();
	blackAnt->addComponent(ANIMATION_COMPONENT, animBlackAnt);

	RenderComponent* renderBlackAnt = new RenderComponent(txtBlackAnt);
	blackAnt->addRenderComponent(renderBlackAnt);
	
	MovementComponentBlackAnt* mvm = new MovementComponentBlackAnt(animBlackAnt);
	blackAnt->addComponent(MOVEMENT_COMPONENT, mvm);

	AddEntity(blackAnt);
	return blackAnt;
}
Entity* RoomScene::createRedAnt(Vector2D pos, MovementComponentFrog* playerMvmCmp) {
	Entity* redAnt = new Entity(this,RED_ANT_ENTITY);
	//textura cambiar
	Texture* txtRedAnt = &sdlutils().images().at("fishSheet");

	TransformComponent* transform = new TransformComponent(pos);
	redAnt->addComponent(TRANSFORM_COMPONENT, transform);

	AnimationComponent* animRedAnt = new AnimationComponent();
	redAnt->addComponent(ANIMATION_COMPONENT, animRedAnt);

	RenderComponent* renderRedAnt = new RenderComponent(txtRedAnt);
	redAnt->addRenderComponent(renderRedAnt);

	MovementComponentRedAnt* mvm = new MovementComponentRedAnt(animRedAnt, playerMvmCmp);
	redAnt->addComponent(MOVEMENT_COMPONENT, mvm);

	AddEntity(redAnt);
	return redAnt;
}
Entity* RoomScene::createCockroach(Vector2D pos) {
	Entity* cockroach = new Entity(this, COCKROACH_ENTITY);
	//textura cambiar
	Texture* txtcockroach = &sdlutils().images().at("fishSheet");//supongo que esto estaba de placeholder

	TransformComponent* transform = new TransformComponent(pos);
	cockroach->addComponent(TRANSFORM_COMPONENT, transform);

	AnimationComponent* animcockroach = new AnimationComponent();
	cockroach->addComponent(ANIMATION_COMPONENT, animcockroach);

	RenderComponent* renderanimcockroach = new RenderComponent(txtcockroach);
	cockroach->addRenderComponent(renderanimcockroach);

	MovementComponentCockroach* mvm = new MovementComponentCockroach(animcockroach);
	cockroach->addComponent(MOVEMENT_COMPONENT, mvm);

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
	animDoor->addAnimation("IDLE", Animation({ Vector2D(0,1) }, true, false));
	animDoor->addAnimation("DEATH", Animation({ Vector2D(0,0) }, false, true));
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

	animSnake->addAnimation("IDLE_RIGHT", Animation({ Vector2D(2,0) }, false, false));
	animSnake->addAnimation("IDLE_LEFT", Animation({ Vector2D(2,0) }, true, false));
	animSnake->addAnimation("IDLE_DOWN", Animation({ Vector2D(1,0) }, false, false));
	animSnake->addAnimation("IDLE_UP", Animation({ Vector2D(0,0) }, false, false));
	animSnake->addAnimation("ATTACK_RIGHT", Animation({ Vector2D(2,1) }, false, false));
	animSnake->addAnimation("ATTACK_LEFT", Animation({ Vector2D(2,1) }, true, false));
	animSnake->addAnimation("ATTACK_DOWN", Animation({ Vector2D(1,1) }, false, false));
	animSnake->addAnimation("ATTACK_UP", Animation({ Vector2D(0,1) }, false, false));

	RenderComponentSnake* renderSnake = new RenderComponentSnake(txtSnake, txtNeck, animSnake);
	snake->addRenderComponentSnake(renderSnake);

	MovementComponentSnake* mvmSnake = new MovementComponentSnake(animSnake);
	snake->addComponent(MOVEMENT_COMPONENT, mvmSnake);

	AttackComponentSnake* atckSnake = new AttackComponentSnake();
	snake->addComponent(ATTACK_COMPONENT, atckSnake);

	LifeComponent* lfSnake = new LifeComponent(1, 1);
	lfSnake->setContext(snake);
	lfSnake->initComponent();
	snake->addComponent(LIFE_COMPONENT, lfSnake);

	AddEntity(snake);
	return snake;
}

Entity* RoomScene::createBomb(Vector2D pos) {
	Entity* bomb = new Entity(this, BOMB_ENTITY);
	Texture* textBomb = &sdlutils().images().at("eggSheet");;

	TransformComponent* transform = new TransformComponent(pos);
	bomb->addComponent(TRANSFORM_COMPONENT, transform);

	AnimationComponent* animBomb = new AnimationComponent();
	animBomb->addAnimation("BOMB_IDLE", Animation({ Vector2D(0,0), Vector2D(0,1) }, false, true));
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
Entity* RoomScene::createPiedraMovible(Vector2D pos)
{
	Entity* piedra = new Entity(this, PIEDRAMOV_ENTITY);
	Texture* textBomb = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/PiedraMovible.png", 1, 1);

	TransformComponent* transform = new TransformComponent(pos);
	piedra->addComponent(TRANSFORM_COMPONENT, transform);

	RenderComponent* renderPiedra = new RenderComponent(textBomb);
	piedra->addComponent(RENDER_COMPONENT, renderPiedra);
	piedra->addRenderComponent(renderPiedra);

	Box* boxPiedra = new Box(pos);
	Collider coll = Collider(boxPiedra);
	ColliderComponent* collPiedra = new ColliderComponent(transform);
	piedra->addComponent(COLLIDER_COMPONENT, collPiedra);
	
	TonguePushComponent* tongueInteract = new TonguePushComponent();
	piedra->addComponent(TONGUEINTERACT_COMPONENT, tongueInteract);	

	AddEntity(piedra);
	return piedra;
}
Entity* RoomScene::createEnganche(Vector2D pos)
{
	Entity* enganche = new Entity(this, ENGANCHE_ENTITY);
	Texture* textEnganche = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/EngancheProv.png", 1, 1);

	TransformComponent* transform = new TransformComponent(pos);
	enganche->addComponent(TRANSFORM_COMPONENT, transform);

	RenderComponent* renderEnganche = new RenderComponent(textEnganche);
	enganche->addComponent(RENDER_COMPONENT, renderEnganche);
	enganche->addRenderComponent(renderEnganche);

	Box* boxEnganche = new Box(pos);
	Collider coll = Collider(boxEnganche);
	ColliderComponent* collEnganche = new ColliderComponent(transform);
	enganche->addComponent(COLLIDER_COMPONENT, collEnganche);

	TongueHookComponent* tongueInteract = new TongueHookComponent();
	enganche->addComponent(TONGUEINTERACT_COMPONENT, tongueInteract);

	AddEntity(enganche);
	return enganche;
}
Entity* RoomScene::createMapChanger(string name, Vector2D pos, bool pushed, string nextMap)
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
	e->addComponent(RENDER_COMPONENT, renderC);
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
	destructible->addComponent(RENDER_COMPONENT, renderDestructible);
	destructible->addRenderComponent(renderDestructible);

	Box* boxdestructible = new Box(pos);
	Collider coll = Collider(boxdestructible);
	ColliderComponent* colldestructible = new ColliderComponent(transform);
	destructible->addComponent(COLLIDER_COMPONENT, colldestructible);

	DestructibleComponent* destructibleComponent = new DestructibleComponent(loot, pos);
	destructible->addComponent(DESTRUCTIBLE_COMPONENT, destructibleComponent);

	AddEntity(destructible);
	return destructible;
}
Entity* RoomScene::createArbusto(Vector2D pos, int loot)
{
	// el loot indica que va a soltar cuando se rompa, 0 = loot aleatorio, 1 = vida y 2 = dinero
	Entity* destructible = new Entity(this, DESTRUCTIBLE_ENTITY);
	Texture* txtDestructible = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/placeholderArbusto.png", 1, 1);
	// hay que animarlo

	TransformComponent* transform = new TransformComponent(pos);
	destructible->addComponent(TRANSFORM_COMPONENT, transform);

	RenderComponent* renderDestructible = new RenderComponent(txtDestructible);
	destructible->addComponent(RENDER_COMPONENT, renderDestructible);
	destructible->addRenderComponent(renderDestructible);

	Box* boxdestructible = new Box(pos);
	Collider coll = Collider(boxdestructible);
	ColliderComponent* colldestructible = new ColliderComponent(transform);
	destructible->addComponent(COLLIDER_COMPONENT, colldestructible);

	DestructibleComponent* destructibleComponent = new DestructibleComponent(loot, pos);
	destructible->addComponent(DESTRUCTIBLE_COMPONENT, destructibleComponent);

	return destructible;
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
			MovementComponentFrog* mvmPlayer = dynamic_cast<MovementComponentFrog*>(player->getComponent(MOVEMENT_COMPONENT));
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
			MovementComponentFrog* mvmPlayer = dynamic_cast<MovementComponentFrog*>(player->getComponent(MOVEMENT_COMPONENT));
			c = createRedAnt(pos, mvmPlayer);
		}
	}
	else if (objName == "Snake") {
		c = createSnake(pos);
	}
	else if (objName == "Bomb") {
		c = createBomb(pos);
	}
	else if (objName == "Cockroach") {
		c = createCockroach(pos);
	}
	return c;
}

Entity* RoomScene::createObjInteract(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps, int objIntID, bool objInteracted)
{
	Entity* c = nullptr;
	
	if (objName == "Jarron"){
		//Comentado para que el juego no reviente
		c = createJarron(pos, 0);
		//c = createJarron(pos, objProps[0].getIntValue());
	}	
	else if (objName == "Arbusto")
	{
		c = createArbusto(pos, 0);
		//c = createArbusto(pos, objProps[0].getIntValue());
	}
	else if (objName == "PiedraMovible") {
		c = createPiedraMovible(pos);
	}
	else if (objName == "Enganche") {
		c = createEnganche(pos);
	}

//	else if ()......
//
//	if (objName == "Nombre que le quieras poner a tu objeto"){
//		c = createLoqsea(objProps[0].getStringValue(), objProps[1].getIntValue()); POR EJEMPLO
//Entity* RoomScene::createObjInteract(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps, int objIntID, bool objInteracted)
//{
	//Entity* c = nullptr;

	//int objIntID: id que necesita cada obj para acceder a su pos en el vector del data manager d objetos interactuables

	
	else if (objName == "PiedraMovible"){
		c = createPiedraMovible(pos);
	}	
	else if (objName == "Enganche") {
		c = createEnganche(pos);
	}
	else if (objName == "Palanca" || objName == "Boton") {
		c = createMapChanger(objName, pos, objProps[1].getBoolValue(), objProps[0].getStringValue());
	}
//	Entity* c = nullptr;
//
//	int objIntID: id que necesita cada obj para acceder a su pos en el vector del data manager d objetos interactuables

	return c;
}

Entity* RoomScene::createExplotable(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps) {
	Entity* c = nullptr;
	if (objName == "Puerta Explotable") {
		c = createExplotableDoor(pos);
	}
	return c;
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
			cout << "create player";
			c = createPlayer(pos, 100, 100);
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

	else if (objClass == "Explotable") {
		c = createExplotable(pos, objName, objProps);
	}
	return c;
}

void RoomScene::movePlayer(Vector2D pos)
{
	static_cast<TransformComponent*>(player->getComponent(TRANSFORM_COMPONENT))->resetPos(pos);
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
			it = entityList.erase(it);
			eliminated = true;
		}
		else it++;
	}
}
RoomScene::~RoomScene() {
	//Eliminar la lista de entidades
	for (auto it = entityList.begin(); it != entityList.end(); ++it) {
		delete* it;
	}

	//NO BORREIS LO SINGLETONS, Q SE BORRAN SOLOS
	delete mapReader;
}

void RoomScene::changeMap()
{
	playerOrig = nextFlonk;

	auto it = entityList.begin();
	while (it != entityList.end()) {
		//Por la arquitectura actual, es necesario mantener la entidad de frog.
		//Para cada entidad se comprueba su name, si no es un frog lo borra.
		if ((*it)->getName() != FROG_ENTITY)
			it = entityList.erase(it);
		else
			it++;
	}

	mapReader->clearMap();
	mapReader->loadBg(nextMap, sdlutils().renderer());
	mapReader->loadObj(nextMap);

	cameraManager->setTarget(player);

	needMapChange = false;
}
