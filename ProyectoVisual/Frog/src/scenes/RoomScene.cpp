#include "RoomScene.h"
#include "../components/CrazyFrogIAComponent.h"

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

Entity* RoomScene::createPlayer(Vector2D pos, int boundX, int boundY)
{
	player = new Entity(this);
	Texture* txtFrog = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/ranaSpritesheet.png", 4, 4);
	Texture* txtTongue = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/spritesheetTongue.png", 3, 1);

	AnimationComponent* animFrog = new AnimationComponent();
	RenderComponentFrog* renderFrog = new RenderComponentFrog(txtFrog, txtTongue, animFrog);

	renderFrog->setContext(player);

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
	player->addComponent(MOVEMENT_COMPONENT, mvm);

	AttackComponentFrog* atck = new AttackComponentFrog();
	player->addComponent(ATTACK_COMPONENT, atck);
	atck->setContext(player);

	FrogInputComponent* input = new FrogInputComponent();
	input->setComponents(mvm, atck);
	input->setContext(player);
	player->addComponent(INPUT_COMPONENT, input);

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

	AnimationComponent* animFrog = new AnimationComponent();
	RenderComponentFrog* renderFrog = new RenderComponentFrog(txtFrog, txtTongue, animFrog);

	renderFrog->setContext(frog);

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

Entity* RoomScene::createEnemy(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps)
{
	Entity* c = nullptr;
		
	if (objName == "Crazy frog"){
		c = createCrazyFrog(pos);
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

void RoomScene::movePlayer(Vector2D pos)
{
	static_cast<MovementComponent*>(player->getComponent(MOVEMENT_COMPONENT))->resetPos(pos);
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

void RoomScene::changeMap(std::string nextMap, flonkOrig nextFlonk)
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
}
