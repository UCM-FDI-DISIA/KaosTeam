#pragma once
#include "../ecs/Scene.h"
//#include "../ecs/Entity.h"
#include"../components/MovementComponentFly.h"
#include "../components/RenderComponent.h"
#include "../components/MovementComponentFrog.h"

class RoomScene : public Scene
{
private:
	//Camara
	std::vector<Entity*> entityList;
	MapManager* mapReader;
	int id;
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



		Entity* fly = new Entity(this);
		MovementComponentFly* mvm = new MovementComponentFly(Vector2D(2, 3));
		mvm->setContext(fly);
		fly->addComponent(MOVEMENT_COMPONENT, mvm);

		rndr = new RenderComponent("../Frog/resources/sprites/moscaSpritesheet.png", 1, 3, 0.5);
		rndr->setContext(fly);
		fly->addRenderComponent(rndr);
		entityList.push_back(fly);

	};

	void AddEntity(Entity* entity);
	void Render() override;
	void Update() override;
	virtual ~RoomScene();
	MapManager* getMapReader() { return mapReader; };

};