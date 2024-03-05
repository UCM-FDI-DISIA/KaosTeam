#pragma once
#include "../ecs/Scene.h"
//#include "../ecs/Entity.h"
#include"../components/MovementComponentFly.h"
#include "../components/RenderComponentFrog.h"
#include "../components/AttackComponent.h"
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
		mapReader = new MapManager("resources/maps/H1map.tmx", this);
		//mapReader->load("resources/maps/tileMap_Prueba.tmx", sdlutils().renderer());


		Entity* player = new Entity(this);

		MovementComponent* mvm = new MovementComponentFrog(Vector2D(2, 2));
		mvm->setContext(player);
		player->addComponent(MOVEMENT_COMPONENT, mvm);

		Texture* txtFrog = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/ranaSpritesheet.png", 4, 4);
		Texture* txtTongue = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/spritesheetTongue.png", 3, 1);
		RenderComponent* rndr = new RenderComponentFrog(txtFrog, txtTongue);
		rndr->setContext(player);
		player->addRenderComponent(rndr);

		Component* atck = new AttackComponent();
		player->addComponent(ATTACK_COMPONENT, atck);
		atck->setContext(player);
		entityList.push_back(player);


		//camara
		//cameraManager->getInstance(player, mapReader);
		cameraManager = new Camera(player, mapReader);

		Entity* fly = new Entity(this);
		mvm = new MovementComponentFly(Vector2D(2, 3));
		mvm->setContext(fly);
		fly->addComponent(MOVEMENT_COMPONENT, mvm);


		rndr = new RenderComponent("../Frog/resources/sprites/moscaSpritesheet.png", 1, 3, 0.5);
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