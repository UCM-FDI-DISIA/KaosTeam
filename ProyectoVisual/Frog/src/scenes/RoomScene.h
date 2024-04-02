#pragma once
#include "../ecs/Scene.h"
#include "../components/MovementComponentFly.h"
#include "../components/RenderComponent.h"
#include "../components/RenderComponentFrog.h"
#include "../components/AttackComponentFrog.h"
#include "../components/MovementComponentFrog.h"
#include "../components/FollowPlayerComponent.h"
#include "../components/AnimationComponent.h"
#include "../components/TransitionComponent.h"
#include "../managers/CameraManager.h"
#include "../components/FrogInputComponent.h"
#include "../components/ColliderComponent.h"
#include "../components/MovementComponentFish.h"
#include "../managers/HUDManager.h"
class RoomScene : public Scene
{
private:
	Camera* cameraManager = nullptr;
	std::vector<Entity*> entityList;
	MapManager* mapReader;
	HUDManager* HUD;
	int id;
	Entity* player = nullptr;
	flonkOrig playerOrig = S;

	//Comprueba las colisiones de los objetos de la sala, llamando a OnCollision de Collider si hay colision
	void CheckColisions();
public:
	RoomScene(int id) : id(id) {
		//A trav�s del id de la sala, se deben buscar los datos necesarios para cargar el tilemap y las entidades de la sala.
		mapReader = new MapManager("resources/maps/niveles/nivel01/mapaN1_01.tmx", this);
		mapReader->loadObj("resources/maps/niveles/nivel01/mapaN1_01.tmx");

		//Create player desde el mapa
		cameraManager = Camera::instance();
		cameraManager->setTarget(player);
		HUD = HUDManager::GetInstance();

#pragma region Cosas q vamos a borrar pronto
		Texture* textFly = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/moscaSpritesheet.png", 1, 3);

		Entity* fly = new Entity(this);

		AnimationComponent* animFly = new AnimationComponent();
		RenderComponent* rndrFly = new RenderComponent(textFly, 1, 3, 0.5, animFly);

		rndrFly->setContext(fly);

		Animation a; //Animaciones mosca
		a = Animation({ Vector2D(0,0), Vector2D(0,1) }, false, true);
		animFly->addAnimation("FLY", a);

		fly->addRenderComponent(rndrFly);
		fly->addComponent(ANIMATION_COMPONENT, animFly);

		animFly->playAnimation("FLY");


		MovementComponent* mvm = new MovementComponentFly(Vector2D(0, 3));
		mvm->setContext(fly);
		fly->addComponent(MOVEMENT_COMPONENT, mvm);

		entityList.push_back(fly);


		Entity* flyToPlayer = new Entity(this);

		FollowPlayerComponent* fpc = new FollowPlayerComponent(Vector2D(0, 0));
		fpc->setContext(flyToPlayer);
		flyToPlayer->addComponent(MOVEMENT_COMPONENT, fpc);

		AnimationComponent* animFly2 = new AnimationComponent();
		RenderComponent* rndrFly2 = new RenderComponent(textFly, 1, 3, 0.5, animFly2);
		rndrFly2->setContext(flyToPlayer);

		a = Animation({ Vector2D(0,0), Vector2D(0,1) }, false, true);
		animFly2->addAnimation("FLY", a);

		flyToPlayer->addRenderComponent(rndrFly2);
		flyToPlayer->addComponent(ANIMATION_COMPONENT, animFly2);

		animFly2->playAnimation("FLY");

		//Collider al flyToPlayer para probar las colisiones
		ColliderComponent* collider = new ColliderComponent();
		collider->setContext(flyToPlayer);
		flyToPlayer->addComponent(COLLIDER_COMPONENT, collider);

		entityList.push_back(flyToPlayer);
		createFish(Vector2D(0, 3), 4);

		

#pragma endregion

		
	};
	void AddEntity(Entity* entity);
	void render() override;
	void update() override;
	virtual ~RoomScene();

	MapManager* getMapReader() { return mapReader; };
	void changeMap(std::string nextMap, flonkOrig nextFlonk);

	Entity* createEntity(Vector2D pos, std::string objName, std::string objClass, std::vector<tmx::Property> objProps);

	Entity* createEnemy(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps);
	Entity* createObjInteract(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps);
	Entity* createPlayer(Vector2D pos, int boundX, int boundY);
	Entity* createTransition(std::string objName, std::string nextMap);
	Entity* createCrazyFrog(Vector2D pos);
	Entity* createFish(Vector2D pos, int boundX);

	Entity* getPlayer() { return player; };
	void movePlayer(Vector2D pos);
};