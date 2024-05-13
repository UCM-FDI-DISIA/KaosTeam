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

const int BOSS_X = 560;
const int BOSS_Y = 560;
const int BOSS_SCALE = 7;

class RoomScene : public Scene
{
private:
	Camera* cameraManager;
	std::vector<Entity*> entityList;
	MapManager* mapReader;
	HUDManager* HUD;
	int id;
	Entity* player;
	Entity* francois;
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
	RoomScene(int id);
	virtual ~RoomScene();

	void render() override;
	void update() override;

	void AddEntity(Entity* entity);
	void removeEntity(Entity* entity);
	void changeMap();
	void callForMapChange(std::string nextMap, flonkOrig nextFlonk = S);
	void movePlayer(Vector2D pos);

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
	
	//Getters
	Entity* getPlayer() const { return player; };
	MapManager* getMapReader() const { return mapReader; };
};