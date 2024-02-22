#pragma once
#include "../ecs/Scene.h"
//#include "../ecs/Entity.h"
#include"../components/MovementComponent.h"
#include "../components/RenderComponent.h"

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
		player->addComponent(MOVEMENT_COMPONENT, new MovementComponent(v));
		RenderComponent* rndr = new RenderComponent("../Frog/resources/sprites/unFrameDeRana.png", 1, 1);
		rndr->setContext(player);
		player->addComponent(RENDER_COMPONENT, rndr);
		entityList.push_back(player);
	};

	void AddEntity(Entity* entity);
	void Render() override;
	void Update() override;
	virtual ~RoomScene();

};