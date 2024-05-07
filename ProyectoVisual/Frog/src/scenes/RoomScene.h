#pragma once
#include "../ecs/Scene.h"
//#include "../sdlutils/checkML.h"
#include "../components/MovementComponentFly.h"
#include "../components/RenderComponent.h"
#include "../components/RenderComponentFrog.h"
#include "../components/RenderComponentSnake.h"
#include "../components/AttackComponentFrog.h"
#include "../components/AttackComponentSnake.h"
#include "../components/MovementComponentFrog.h"
#include "../components/FollowPlayerComponent.h"
#include "../components/AnimationComponent.h"
#include "../components/TransitionComponent.h"
#include "../managers/CameraManager.h"
#include "../components/FrogInputComponent.h"
#include "../components/ColliderComponent.h"
#include "../components/MovementComponentFish.h"
#include "../managers/HUDManager.h"
#include "../components/MovementComponentFish.h"
#include "../components/MovementComponentBlackAnt.h"
#include "../components/MovementComponentRedAnt.h"
#include "../components/MovementComponentSnake.h"
#include "../components/DestructibleComponent.h"
#include"../managers/ShopManager.h"
//#include "../components/MoneyComponent.h"
#include "../components/MovementComponentBomb.h"
#include "../components/TonguePushComponent.h"
#include "../components/TongueHookComponent.h"
#include "../components/MapShiftComponent.h"
#include "../components/InventoryComponent.h"
#include "../components/MovementComponentCockroach.h"
#include "../components/AttackComponentBasicEnemy.h"
#include "../components/ExploitableComponent.h"
#include "../components/ConveyorBeltComponent.h"
#include "../components/SwallowComponent.h"
#include "../components/ItemThrowerComponent.h"
class Texture;
class RoomScene : public Scene
{
private:
	Camera* cameraManager;
	std::vector<Entity*> entityList;
	MapManager* mapReader;
	HUDManager* HUD;
	string path;
	Entity* player;
	flonkOrig playerOrig;
	flonkOrig nextFlonk;
	bool needMapChange;
	std::string nextMap;
	Shop* shopManager;
	bool insideShop; //se activa cuando se haga la transicion para entrar a la tienda y se desactiva al salir
	Texture& arbolTiendaTex;
	int arbolX, arbolY;
	bool showArbol;
		/*Comprueba las colisiones de los objetos de la sala, llamando a OnCollision de Collider si hay colision
	Por tanto, hay dos OnCollision por cada colision.
	*/
	void CheckColisions();

public:
	RoomScene(string path) : path(path), cameraManager(nullptr), player(nullptr), playerOrig(N), nextFlonk(S), needMapChange(false), insideShop(false),arbolTiendaTex(sdlutils().images().at("arbolTienda")) {
		//A trav�s del id de la sala, se deben buscar los datos necesarios para cargar el tilemap y las entidades de la sala.

		mapReader = new MapManager(path, this);
		mapReader->loadObj(path);

		//Create player desde el mapa
		cameraManager = Camera::instance();
		cameraManager->setTarget(player);
		HUD = HUDManager::instance();
		shopManager = Shop::instance();
		shopManager->setPlayer(player);
		shopManager->setHUD(HUD);


#pragma region Cosas q vamos a borrar pronto
#pragma endregion

		
	};

	void AddEntity(Entity* entity);
	void removeEntity(Entity* entity);
	void render() override;
	void update() override;
	virtual ~RoomScene();

	MapManager* getMapReader() { return mapReader; };
	string getPath() { return path; }
	void changeMap();
	void callForMapChange(std::string nextMap, flonkOrig nextFlonk = S){ this->nextMap = nextMap; this->nextFlonk = nextFlonk;  needMapChange = true; };

	Entity* createEntity(Vector2D pos, std::string objName, std::string objClass, std::vector<tmx::Property> objProps, int objIntID, bool objInteracted = false);
	Entity* createEnemy(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps);
	Entity* createObjInteract(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps, int objIntID, bool objInteracted = false);
	Entity* createExplotable(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps);
	Entity* createPlayer(Vector2D pos, int boundX, int boundY);
	Entity* createTransition(Vector2D pos, std::string objName, std::string nextMap);
	Entity* createCrazyFrog(Vector2D pos);
	Entity* createFish(Vector2D pos, int boundX);
	Entity* createBlackAnt(Vector2D pos, MovementComponentFrog* playerMvmCmp);
	Entity* createRedAnt(Vector2D pos, MovementComponentFrog* playerMvmCmp);
	Entity* createSnake(Vector2D pos);
	Entity* createJarron(Vector2D pos, int loot);
	Entity* createArbusto(Vector2D pos, int loot);
	Entity* createBomb(Vector2D pos);
	Entity* createPiedraMovible(Vector2D pos, int objIntID);
	Entity* createEnganche(Vector2D pos);
	Entity* createCogible(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps);

	Entity* createMapChanger(string name, Vector2D pos, bool pushed, string nextMap, int objIntID, bool objInteracted);
	Entity* createCockroach(Vector2D pos);
	Entity* createExplotableDoor(Vector2D pos);
	Entity* createConveyorBelt(Vector2D pos, int orientation);

	Entity* getPlayer() { return player; };
	void movePlayer(Vector2D pos);
};