#pragma once

#include "../ecs/Scene.h"
#include "../managers/HUDManager.h"
#include "../managers/CameraManager.h"
#include "../managers/MapManager.h"
#include "../ecs/Entity.h"
#include <vector>

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

	/*Comprueba las colisiones de los objetos de la sala, llamando a OnCollision de Collider si hay colision
	Por tanto, hay dos OnCollision por cada colision.
	*/
	void CheckColisions();
public:
	RoomScene(int id);
	virtual ~RoomScene();

	void render() override;
	void update() override;

	//Create Entities
	Entity* createEntity(Vector2D pos, std::string objName, std::string objClass, std::vector<tmx::Property> objProps);
	Entity* createEnemy(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps);
	Entity* createObjInteract(Vector2D pos, std::string objName, std::vector<tmx::Property> objProps);
	Entity* createPlayer(Vector2D pos, int boundX, int boundY);
	Entity* createTransition(std::string objName, std::string nextMap);
	Entity* createCrazyFrog(Vector2D pos);
	Entity* createFish(Vector2D pos, int boundX);
	Entity* createBlackAnt(Vector2D pos, MovementComponentFrog* playerMvmCmp);
	Entity* createRedAnt(Vector2D pos, MovementComponentFrog* playerMvmCmp);
	Entity* createSnake(Vector2D pos);
	Entity* createFrancois(Vector2D pos);
	
	void AddEntity(Entity* entity);
	void changeMap();
	void callForMapChange(std::string nextMap, flonkOrig nextFlonk);
	void movePlayer(Vector2D pos);
	
	//Getters
	Entity* getPlayer() const { return player; };
	MapManager* getMapReader() const { return mapReader; };
};