#include "RoomScene.h"
#include "../components/CrazyFrogIAComponent.h"

void RoomScene::render() {
	mapReader->draw(sdlutils().renderer());

	for (Entity* e : entityList) {
		if (e != nullptr)
			e->render();
	}
	HUD->render();
}

void RoomScene::update() {
	for (Entity* e : entityList) {
		if (e != nullptr)
		e->update();
	}

	cameraManager->update();
	if (insideShop) shopManager->update();
	if (needMapChange)
		changeMap();
	//comrpueba las colisiones con la rana
	CheckColisions();
}

void RoomScene::CheckColisions() {
	for (Entity* e1 : entityList) {
		ColliderComponent* coll1 = static_cast<ColliderComponent*>(e1->getComponent(COLLIDER_COMPONENT));
		if (coll1 != nullptr)
			for (Entity* e2 : entityList) {
				coll1->CheckCollision(e2);
			}
	}
};

Entity* RoomScene::createPlayer(Vector2D pos, int boundX, int boundY)
{
	player = new Entity(this);
	Texture* txtFrog = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/ranaSpritesheet.png", 4, 5);
	Texture* txtTongue = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/spritesheetTongue.png", 3, 1);

	TransformComponent* transform = new TransformComponent(pos);
	player->addComponent(TRANSFORM_COMPONENT, transform);
	transform->setContext(player);

	ColliderComponent* collider = new ColliderComponent(transform);
	player->addComponent(COLLIDER_COMPONENT, collider);
	collider->setContext(player);

	AnimationComponent* animFrog = new AnimationComponent();
	RenderComponentFrog* renderFrog = new RenderComponentFrog(txtFrog, txtTongue, animFrog);

	renderFrog->setContext(player);
	renderFrog->initComponent();

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

	player->addRenderComponentFrog(renderFrog);
	player->addComponent(ANIMATION_COMPONENT, animFrog);

	MovementComponentFrog* mvm = new MovementComponentFrog(pos, animFrog);
	mvm->setContext(player);
	mvm->initComponent();
	player->addComponent(MOVEMENT_COMPONENT, mvm);

	AttackComponentFrog* atck = new AttackComponentFrog();
	player->addComponent(ATTACK_COMPONENT, atck);
	atck->setContext(player);

	FrogInputComponent* input = new FrogInputComponent();
	input->setComponents(mvm, atck);
	input->setContext(player);
	player->addComponent(INPUT_COMPONENT, input);

	//Sistema de colisiones
	ColliderComponent* coll = new ColliderComponent();
	coll->setContext(player);
	player->addComponent(COLLIDER_COMPONENT, coll);

	MoneyComponent* moneyComp = new MoneyComponent();
	moneyComp->setContext(player);
	player->addComponent(MONEY_COMPONENT, moneyComp);
	
	AddEntity(player);

	return player;
}

Entity* RoomScene::createTransition(std::string objName, std::string nextMap) {
	Entity* c = new Entity(this);

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
	else {
		nextFlonk = S;
	}

	TransitionComponent* trans = new TransitionComponent(nextMap, nextFlonk);
	c->addComponent(TRANSITION_COMPONENT, trans);
	trans->setContext(c);

	//entityList.push_back(c); add entity ya hace esto

	AddEntity(c);

	return c;
}

Entity* RoomScene::createCrazyFrog(Vector2D pos)
{
	Entity* frog = new Entity(this);
	Texture* txtFrog = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/ranaLocaSpritesheet.png", 4, 4);
	Texture* txtTongue = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/spritesheetTongue.png", 3, 1);

	TransformComponent* transform = new TransformComponent(pos);
	frog->addComponent(TRANSFORM_COMPONENT, transform);
	transform->setContext(frog);

	AnimationComponent* animFrog = new AnimationComponent();
	RenderComponentFrog* renderFrog = new RenderComponentFrog(txtFrog, txtTongue, animFrog);

	renderFrog->setContext(frog);
	renderFrog->initComponent();

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
	mvm->setContext(frog);
	mvm->initComponent();
	frog->addComponent(MOVEMENT_COMPONENT, mvm);

	AttackComponentFrog* atck = new AttackComponentFrog();
	frog->addComponent(ATTACK_COMPONENT, atck);
	atck->setContext(frog);

	CrazyFrogIAComponent* IA = new CrazyFrogIAComponent(mvm, atck);
	frog->addComponent(IACOMPONENT, IA);
	IA->setContext(frog);

	AddEntity(frog);
	return frog;
}
Entity* RoomScene::createFish(Vector2D pos, int boundX) {
	Entity* fish = new Entity(this);
	Texture* txtFish = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/spritesheetFish.png", 1, 3);

	TransformComponent* transform = new TransformComponent(pos);
	fish->addComponent(TRANSFORM_COMPONENT, transform);
	transform->setContext(fish);

	AnimationComponent* animFish = new AnimationComponent();
	RenderComponent* renderFish = new RenderComponent(txtFish, 1, 3, 1, animFish);
	renderFish->setContext(fish);
	renderFish->initComponent();

	animFish->addAnimation("RIGHT", Animation({ Vector2D(0,1), Vector2D(0,2) }, true, false));
	animFish->addAnimation("LEFT", Animation({ Vector2D(0,1), Vector2D(0,2) }, false, false));
	animFish->addAnimation("JUMP_RIGHT", Animation({ Vector2D(0,0) }, true, false));
	animFish->addAnimation("JUMP_LEFT", Animation({ Vector2D(0,0) }, false, false));

	fish->addComponent(ANIMATION_COMPONENT, animFish);
	animFish->setContext(fish);

	fish->addRenderComponent(renderFish);

	//el limite tiene que ser una propiedad
	MovementComponentFish* mvm = new MovementComponentFish(boundX, animFish);
	mvm->setContext(fish);
	mvm->initComponent();
	fish->addComponent(MOVEMENT_COMPONENT, mvm);

	AddEntity(fish);
	return fish;	
}
Entity* RoomScene::createBlackAnt(Vector2D pos, MovementComponentFrog* playerMvmCmp) {
	Entity* blackAnt = new Entity(this);
	//textura cambiar
	Texture* txtBlackAnt = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/spritesheetFish.png", 1, 3);

	TransformComponent* transform = new TransformComponent(pos);
	blackAnt->addComponent(TRANSFORM_COMPONENT, transform);
	transform->setContext(blackAnt);

	AnimationComponent* animBlackAnt = new AnimationComponent();
	RenderComponent* renderBlackAnt = new RenderComponent(txtBlackAnt, 1, 3, 0.5, animBlackAnt);

	renderBlackAnt->setContext(blackAnt);
	renderBlackAnt->initComponent();


	blackAnt->addRenderComponent(renderBlackAnt);
	blackAnt->addComponent(ANIMATION_COMPONENT, animBlackAnt);
	
	MovementComponentBlackAnt* mvm = new MovementComponentBlackAnt(animBlackAnt);
	mvm->setContext(blackAnt);
	blackAnt->addComponent(MOVEMENT_COMPONENT, mvm);

	AddEntity(blackAnt);
	return blackAnt;
}
Entity* RoomScene::createRedAnt(Vector2D pos, MovementComponentFrog* playerMvmCmp) {
	Entity* redAnt = new Entity(this);
	//textura cambiar
	Texture* txtRedAnt = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/spritesheetFish.png", 1, 3);

	TransformComponent* transform = new TransformComponent(pos);
	redAnt->addComponent(TRANSFORM_COMPONENT, transform);
	transform->setContext(redAnt);

	AnimationComponent* animRedAnt = new AnimationComponent();
	RenderComponent* renderRedAnt = new RenderComponent(txtRedAnt, 1, 3, 0.5, animRedAnt);

	renderRedAnt->setContext(redAnt);
	//animaciones

	redAnt->addRenderComponent(renderRedAnt);
	redAnt->addComponent(ANIMATION_COMPONENT, animRedAnt);

	MovementComponentRedAnt* mvm = new MovementComponentRedAnt(animRedAnt, playerMvmCmp);
	mvm->setContext(redAnt);
	mvm->initComponent();
	redAnt->addComponent(MOVEMENT_COMPONENT, mvm);

	AddEntity(redAnt);
	return redAnt;
}

Entity* RoomScene::createSnake(Vector2D pos) {
	Entity* snake = new Entity(this);
	Texture* txtSnake = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/SnakeSpriteSheet.png", 4, 2);
	Texture* txtNeck = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/SnakeSpriteSheetAttack.png", 2, 1);

	TransformComponent* transform = new TransformComponent(pos);
	snake->addComponent(TRANSFORM_COMPONENT, transform);
	transform->setContext(snake);

	ColliderComponent* collider = new ColliderComponent(transform);
	snake->addComponent(COLLIDER_COMPONENT, collider);
	collider->setContext(snake);

	AnimationComponent* animSnake = new AnimationComponent();
	//RenderComponent* renderSnake = new RenderComponent(txtSnake, 4, 4, 1, animSnake);
	//renderSnake->setContext(snake);
	//RenderComponentFrog* renderFrog = new RenderComponentFrog(txtFrog, txtTongue, animFrog);

	RenderComponentSnake* renderSnake = new RenderComponentSnake(txtSnake, txtNeck, animSnake);

	renderSnake->setContext(snake);
	renderSnake->initComponent();

	animSnake->addAnimation("IDLE_RIGHT", Animation({ Vector2D(2,0) }, false, false));
	animSnake->addAnimation("IDLE_LEFT", Animation({ Vector2D(2,0) }, true, false));
	animSnake->addAnimation("IDLE_DOWN", Animation({ Vector2D(1,0) }, false, false));
	animSnake->addAnimation("IDLE_UP", Animation({ Vector2D(0,0) }, false, false));
	animSnake->addAnimation("ATTACK_RIGHT", Animation({ Vector2D(2,1) }, false, false));
	animSnake->addAnimation("ATTACK_LEFT", Animation({ Vector2D(2,1) }, true, false));
	animSnake->addAnimation("ATTACK_DOWN", Animation({ Vector2D(1,1) }, false, false));
	animSnake->addAnimation("ATTACK_UP", Animation({ Vector2D(0,1) }, false, false));

	snake->addComponent(ANIMATION_COMPONENT, animSnake);
	animSnake->setContext(snake);

	snake->addRenderComponentSnake(renderSnake);

	MovementComponentSnake* mvmSnake = new MovementComponentSnake(animSnake);
	mvmSnake->setContext(snake);
	mvmSnake->initComponent(); //INICIALIZAMOS LOS TRANSFORM (DE LO CONTARIO, PETARÍA)
	snake->addComponent(MOVEMENT_COMPONENT, mvmSnake);

	AttackComponentSnake* atckSnake = new AttackComponentSnake();
	atckSnake->setContext(snake);
	snake->addComponent(ATTACK_COMPONENT, atckSnake);

	AddEntity(snake);
	return snake;
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
	/*
	else if ()......
	*/

	return c;
}


Entity* RoomScene::createObjInteract(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps, int objIntID, bool objInteracted)
{
	Entity* c = nullptr;

	//int objIntID: id que necesita cada obj para acceder a su pos en el vector del data manager d objetos interactuables

	/*
	if (objName == "Nombre que le quieras poner a tu objeto"){
		c = createLoqsea(objProps[0].getStringValue(), objProps[1].getIntValue()); POR EJEMPLO
	}
	else if ()......
	*/

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
		c = createTransition(objName, objProps[0].getStringValue());
	}
	return c;
}

void RoomScene::movePlayer(Vector2D pos)
{
	static_cast<TransformComponent*>(player->getComponent(TRANSFORM_COMPONENT))->resetPos(pos);
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
	delete shopManager;
}

void RoomScene::changeMap()
{
	playerOrig = nextFlonk;

	//borramos entidades(objetos del mapa actual)
	auto it = entityList.begin();
	++it; //la primera es flonk, no le borramos
	while (it != entityList.end()) {
		it = entityList.erase(it);
	}

	mapReader = new MapManager(nextMap, this);
	mapReader->loadObj(nextMap);

	cameraManager->setTarget(player);

	needMapChange = false;
}
