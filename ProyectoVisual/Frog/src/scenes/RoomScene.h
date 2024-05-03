#pragma once

#include "../ecs/Scene.h"
#include "../managers/HUDManager.h"
#include "../managers/CameraManager.h"
#include "../managers/MapManager.h"
#include "../ecs/Entity.h"
#include "../components/TransitionComponent.h"
#include "../managers/ShopManager.h"
#include "../components/MovementComponentFrog.h"
#include <vector>

#include "../components/MovementComponentFish.h"
#include "../components/MovementComponentBlackAnt.h"
#include "../components/MovementComponentRedAnt.h"
#include "../components/MovementComponentSnake.h"
#include "../components/RenderComponentDestructible.h"
#include "../components/DestructibleComponent.h"
#include "../components/MoneyComponent.h"
#include "../components/MovementComponentBomb.h"
#include "../components/TonguePushComponent.h"
#include "../components/TongueHookComponent.h"
#include "../components/MapShiftComponent.h"
#include "../components/InventoryComponent.h"
#include "../components/MovementComponentCockroach.h"
#include "../components/ExploitableComponent.h"

class RoomScene : public Scene
{
private:
	Camera* cameraManager;
	std::vector<Entity*> entityList;
	MapManager* mapReader;
	HUDManager* HUD;
	int id;
	Entity* player;
	flonkOrig playerOrig; //Indica en que punto cardinal aparece Flonk al entrar en cada sala
	bool needMapChange;
	std::string nextMap;
	flonkOrig nextFlonk;
	Shop* shopManager;
	bool insideShop; //se activa cuando se haga la transicion para entrar a la tienda y se desactiva al salir

	/*Comprueba las colisiones de los objetos de la sala, llamando a OnCollision de Collider si hay colision
	Por tanto, hay dos OnCollision por cada colision.
	*/
	void CheckColisions();

public:
	RoomScene(int id) : id(id), cameraManager(nullptr), player(nullptr), playerOrig(S), needMapChange(false), insideShop(false) {
		//A trav�s del id de la sala, se deben buscar los datos necesarios para cargar el tilemap y las entidades de la sala.
		std::string initMapPath = "resources/maps/niveles/nivel02/fuera/mapaN2_08_fuera.tmx";

		mapReader = new MapManager(initMapPath, this);
		mapReader->loadObj(initMapPath);

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
	void changeMap();
	void callForMapChange(std::string nextMap, flonkOrig nextFlonk = S){ this->nextMap = nextMap; this->nextFlonk = nextFlonk;  needMapChange = true; };

	Entity* createEntity(Vector2D pos, std::string objName, std::string objClass, std::vector<tmx::Property> objProps, int objIntID, bool objInteracted = false);
	Entity* createEnemy(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps);
	Entity* createTransition(Vector2D pos, std::string objName, std::string nextMap);
	Entity* createObjInteract(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps, int objIntID, bool objInteracted = false);
	Entity* createExplotable(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps);
	Entity* createPlayer(Vector2D pos, int boundX, int boundY);
	Entity* createCrazyFrog(Vector2D pos);
	Entity* createFish(Vector2D pos, int boundX);
	Entity* createBlackAnt(Vector2D pos, MovementComponentFrog* playerMvmCmp);
	Entity* createRedAnt(Vector2D pos, MovementComponentFrog* playerMvmCmp);
	Entity* createSnake(Vector2D pos);
	Entity* createDestructible(Vector2D pos, int type, int loot);
	Entity* createBomb(Vector2D pos);
	Entity* createFrancois(Vector2D pos);
	Entity* createPiedraMovible(Vector2D pos);
	Entity* createEnganche(Vector2D pos);
	Entity* createMapChanger(string name, Vector2D pos, bool pushed, string nextMap);
	Entity* createCockroach(Vector2D pos);
	Entity* createExplotableDoor(Vector2D pos);
	void movePlayer(Vector2D pos);
	
	//Getters
	Entity* getPlayer() const { return player; };
	MapManager* getMapReader() const { return mapReader; };
};