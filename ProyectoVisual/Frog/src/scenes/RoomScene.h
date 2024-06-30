#pragma once

#include "../ecs/Scene.h"
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
#include "../components/DamageBehaviourComponent.h"
#include "../components/CrazyFrogIAComponent.h"
#include "../components/LifeComponent.h"
#include "../components/CogibleObjectComponent.h"
#include "../components/PuertaComponent.h"
#include "../components/MovementComponentHeadRoach.h"
#include "../managers/MapManager.h"
#include "../ecs/Entity.h"
#include "../components/ConveyorBeltComponent.h"
#include <vector>

const int BOSS_X = 560;
const int BOSS_Y = 560;
const int BOSS_SCALE = 7;


class Texture;
class RoomScene : public Scene
{
private:
	//Game* game;
	Camera* cameraManager;
	std::vector<Entity*> entityList;
	MapManager* mapReader;
	HUDManager* HUD;
	string path;
	Entity* player;
	flonkOrig nextFlonk;
	Entity* francois;
	flonkOrig playerOrig; //Indica en que punto cardinal aparece Flonk al entrar en cada sala
	bool needMapChange;
	std::string nextMap;
	Shop* shopManager;
	bool insideShop; //se activa cuando se haga la transicion para entrar a la tienda y se desactiva al salir
	bool gameOver; //Booleano que se activa solamente en el caso de que que Flonk muera
	//Entity* lastTransition; //Para guardar la ultima transicion con la que ha interatuado Flonk
	Vector2D lastFrogPosition; //ultima posicion de respawn de la rana (se actualiza en cada llamada a changeMap())

	/*Comprueba las colisiones de los objetos de la sala, llamando a OnCollision de Collider si hay colision
	Por tanto, hay dos OnCollision por cada colision.*/
	void CheckColisions();

public:
	RoomScene(string path) : path(path), cameraManager(nullptr), player(nullptr), francois(nullptr), playerOrig(N), nextFlonk(S), needMapChange(false), insideShop(false), gameOver(false) {
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
	};
	virtual ~RoomScene();

	string getPath() { return path; }

	void render() override;
	void update() override;

	void AddEntity(Entity* entity);
	void removeEntity(Entity* entity);
	void changeMap();
	void callForMapChange(std::string nextMap, flonkOrig nextFlonk = S);
	void resetScene(string path);
	void movePlayer(Vector2D pos);
	void revivePlayer();

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
	Entity* createDoor(Vector2D pos);
	Entity* createJarron(Vector2D pos, int loot);
	Entity* createArbusto(Vector2D pos, int loot);
	Entity* createBomb(Vector2D pos);
	Entity* createFrancois();
	Entity* createEnganche(Vector2D pos);
	Entity* createCogible(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps);
	Entity* createPiedraMovible(Vector2D pos, int objIntID);
	Entity* createTroncoTermitas(Vector2D pos);
	Entity* createTermita(Vector2D pos);
	Entity* createMapChanger(string name, Vector2D pos, bool pushed, string nextMap, int objIntID, bool objInteracted);
	Entity* createCockroach(Vector2D pos);
	Entity* createHeadCockroach(Vector2D pos, bool move);
	Entity* createExplotableDoor(Vector2D pos);
	Entity* createConveyorBelt(Vector2D pos, int orientation);
	Entity* createLifeFly(Vector2D pos);
	Entity* createMoneda(Vector2D pos, MonedaType type);
	Entity* createBeer(Vector2D pos);
	Entity* createApple(Vector2D pos);
	Entity* createSalt(Vector2D pos);
	Entity* createWine(Vector2D pos);
	Entity* createCheese(Vector2D pos);
	Entity* createBaguette(Vector2D pos);
	Entity* createEmptyInaccesible(Vector2D pos);

	//Getters
	Entity* getPlayer() const { return player; };
	MapManager* getMapReader() const { return mapReader; };
	bool getGameOverState() { return gameOver; };
};