#pragma once
#include "../ecs/Component.h"
#include "../scenes/RoomScene.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"

class MapShiftComponent :public Component
{
private:
	void trigger(); //hace los cambios en el mapa que se necesiten
	void collisionPalanca(Entity* ent, Collider c);
	void collisionBoton(Entity* ent, Collider c);
	string _nextMap;
	bool shifted = false;

public:
	MapShiftComponent(string nextMap) { _nextMap = nextMap; };
	virtual ~MapShiftComponent() {};
	void initComponent() override;  //Aqui inicializamos los punteros a otros componentes que vayamos a utilizar
};


