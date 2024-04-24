#include "RoomScene.h"

#pragma region includes
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
#include "../components/MovementComponentFish.h"
#include "../components/MovementComponentFrancois.h"
#pragma endregion

RoomScene::RoomScene(int id) : id(id), 
				cameraManager(Camera::instance()), // 
				mapReader(new MapManager("resources/maps/niveles/nivel01/mapaN1_01.tmx", this)), //
				HUD(HUDManager::GetInstance()), //
				player(nullptr), //
				playerOrig(S), //
				needMapChange(false) //
{
	//A trav�s del id de la sala, se deben buscar los datos necesarios para cargar el tilemap 
	// y las entidades de la sala.
	mapReader->loadObj("resources/maps/niveles/nivel01/mapaN1_01.tmx");
	//Create player desde el mapa
	cameraManager->setTarget(player);
	createFrancois(Vector2D(0,0));
};

RoomScene::~RoomScene() {
	//Eliminar la lista de entidades
	for (auto it = entityList.begin(); it != entityList.end(); ++it) {
		delete* it;
	}
	delete mapReader;
}

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
	if (needMapChange)
		changeMap();
	//comrpueba las colisiones con la rana

}

void RoomScene::CheckColisions() {
	for (Entity* e1 : entityList) {
		ColliderComponent* coll1 = e1->getComponent<ColliderComponent>(COLLIDER_COMPONENT);
		if (coll1 != nullptr)
			for (Entity* e2 : entityList) {
				ColliderComponent* coll2 = e2->getComponent<ColliderComponent>(COLLIDER_COMPONENT);
				if (coll2 != nullptr && coll2->CheckCollision(e1))
					coll2->OnCollision(e1);
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

Entity* RoomScene::createFrancois(Vector2D pos)
{
	Entity* fran = new Entity(this);
	MovementComponentFrancois* move = new MovementComponentFrancois();
	fran->addComponent(MOVEMENT_COMPONENT, move);
	move->setContext(fran);
	TransformComponent* tr = new TransformComponent(pos);
	fran->addComponent(TRANSFORM_COMPONENT, tr);
	tr->setContext(fran);
	RenderComponent* rend = new RenderComponent(&sdlutils().images().at("shadow"),1);
	fran->addComponent(RENDER_COMPONENT, rend);
	rend->setContext(fran);
	ColliderComponent* bossColl = new ColliderComponent();
	fran->addComponent(COLLIDER_COMPONENT, bossColl);
	bossColl->setContext(fran);
	MovementComponentFrancois* move = new MovementComponentFrancois();
	fran->addComponent(MOVEMENT_COMPONENT, move);
	move->setContext(fran);
	BossComponent* bossComp = new BossComponent();
	fran->addComponent(BOSS_COMPONENT, bossComp);
	bossComp->setContext(fran);
	AddEntity(fran);
	
	return fran;
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
			MovementComponentFrog* mvmPlayer = player->getComponent<MovementComponentFrog>(MOVEMENT_COMPONENT);
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
			MovementComponentFrog* mvmPlayer = player->getComponent<MovementComponentFrog>(MOVEMENT_COMPONENT);
			c = createRedAnt(pos, mvmPlayer);
		}

	}
	else if (objName == "Snake") {
		c = createSnake(pos);
	}
	else if (objName == "Francois") {
		c = createFrancois(pos);
	}
	/*
	else if ()......
	*/

	return c;
}


Entity* RoomScene::createObjInteract(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps)
{
	Entity* c = nullptr;

	/*
	if (objName == "Nombre que le quieras poner a tu objeto"){
		c = createLoqsea(objProps[0].getStringValue(), objProps[1].getIntValue()); POR EJEMPLO
	}
	else if ()......
	*/

	return c;
}

Entity* RoomScene::createEntity(Vector2D pos, std::string objName, std::string objClass, std::vector<tmx::Property> objProps)
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
		c = createObjInteract(pos, objName, objProps);
	}
	else if (objClass == "Transition") {		
		c = createTransition(objName, objProps[0].getStringValue());
	}
	return c;
}

void RoomScene::AddEntity(Entity* entity) {
	entityList.push_back(entity);
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

void RoomScene::callForMapChange(std::string nextMap, flonkOrig nextFlonk)
{
	this->nextMap = nextMap; this->nextFlonk = nextFlonk;  needMapChange = true;
}

void RoomScene::movePlayer(Vector2D pos)
{
	player->getComponent<TransformComponent>(TRANSFORM_COMPONENT)->resetPos(pos);
}
