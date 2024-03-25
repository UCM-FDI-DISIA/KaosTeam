#pragma once
#include "../ecs/Scene.h"
#include "../components/MovementComponentFly.h"
#include "../components/RenderComponent.h"
#include "../components/RenderComponentFrog.h"
#include "../components/AttackComponentFrog.h"
#include "../components/MovementComponentFrog.h"
#include "../components/FollowPlayerComponent.h"
#include "../components/AnimationComponent.h"
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
	RoomScene(int id) : Scene(true), id(id) {
		//A trav�s del id de la sala, se deben buscar los datos necesarios para cargar el tilemap y las entidades de la sala.
		mapReader = new MapManager("resources/maps/H1map.tmx", this);
		//mapReader->load("resources/maps/tileMap_Prueba.tmx", sdlutils().renderer());

		//Create player desde el mapa
		//Camara despues del mapa
		//camara
		cameraManager = Camera::instance();
		cameraManager->setTarget(player);

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

		entityList.push_back(flyToPlayer);
		
	};

	void AddEntity(Entity* entity);
	void render() override;
	void update() override;
	virtual ~RoomScene();
	MapManager* getMapReader() { return mapReader; };
	Entity* getPlayer() { return player; };

	void createPlayer(std::string texPath, Vector2D pos, int boundX, int boundY);

};