#pragma once
#include "../ecs/Scene.h"
#include "../ecs/Entity.h"

class RoomScene : public Scene
{
private:
	//Camara
	std::vector<Entity*> entityList;
	MapComponent* mapReader;
	int id;
public:
	RoomScene(int id) : id(id) {
		//A través del id de la sala, se deben buscar los datos necesarios para cargar el tilemap y las entidades de la sala.
		mapReader = new MapComponent("tileMap_Prueba");
		mapReader->load("resources/maps/tileMap_Prueba.tmx", sdlutils().renderer());
	};
	void AddEntity(Entity* entity);
	void Render() override;
	void Update() override;
};