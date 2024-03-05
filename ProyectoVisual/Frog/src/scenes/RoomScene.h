#pragma once
#include "../ecs/Scene.h"
//#include "../ecs/Entity.h"
#include"../components/MovementComponentFly.h"
#include "../components/RenderComponent.h"
#include "../components/MovementComponentFrog.h"
#include "../components/FollowPlayerComponent.h"
#include "../managers/CameraManager.h"

class RoomScene : public Scene
{
private:
	Camera* cameraManager = nullptr;
	std::vector<Entity*> entityList;
	MapManager* mapReader;
	int id;
	Entity* player = nullptr;
public:
	RoomScene(int id) : id(id) {
		//A trav�s del id de la sala, se deben buscar los datos necesarios para cargar el tilemap y las entidades de la sala.
		mapReader = new MapManager("tileMap_Prueba");
		mapReader->load("resources/maps/tileMap_Prueba.tmx", sdlutils().renderer());

		Entity* player = new Entity(this);
		Vector2D v(2, 2);
		player->addComponent(MOVEMENT_COMPONENT, new MovementComponentFrog(v));
		RenderComponent* rndr = new RenderComponent("../Frog/resources/sprites/ranaSpritesheet.png", 4, 4);
		rndr->setContext(player);
		player->addRenderComponent(rndr);
		entityList.push_back(player);

		//camara
		//cameraManager->getInstance(player, mapReader);
		cameraManager = new Camera(player, mapReader);

		Entity* fly = new Entity(this);
		MovementComponentFly* mvm = new MovementComponentFly(Vector2D(2, 3));
		mvm->setContext(fly);
		fly->addComponent(MOVEMENT_COMPONENT, mvm);
		RenderComponent* rndr = new RenderComponent("../Frog/resources/sprites/moscaSpritesheet.png", 1, 3, 0.5);
		rndr->setContext(fly);
		fly->addRenderComponent(rndr);
		entityList.push_back(fly);

		
		Entity* flyToPlayer = new Entity(this);
		FollowPlayerComponent* fpc = new FollowPlayerComponent(Vector2D(0, 0));
		fpc->setContext(flyToPlayer);
		flyToPlayer->addComponent(MOVEMENT_COMPONENT, fpc);
		rndr = new RenderComponent("../Frog/resources/sprites/moscaSpritesheet.png", 1, 3, 0.5);
		rndr->setContext(flyToPlayer);
		flyToPlayer->addRenderComponent(rndr);
		entityList.push_back(flyToPlayer);
		
	};

	void AddEntity(Entity* entity);
	void Render() override;
	void Update() override;
	//void HandleEvents(const SDL_Event& event) override;
	virtual ~RoomScene();
	MapManager* getMapReader() { return mapReader; };
	Entity* getPlayer() { return player; };
	void createPlayer(std::string texPath, Vector2D pos);

};