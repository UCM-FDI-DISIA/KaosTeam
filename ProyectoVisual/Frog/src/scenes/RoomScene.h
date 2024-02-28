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
		mapReader = new MapManager("resources/maps/H1map.tmx", this);
	};

	void AddEntity(Entity* entity);
	void Render() override;
	void Update() override;
	virtual ~RoomScene();
	MapManager* getMapReader() { return mapReader; };
	void createPlayer(std::string texPath, Vector2D pos);

};