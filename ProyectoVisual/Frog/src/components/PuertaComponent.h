#pragma once
#include "../ecs/Component.h"
#include "../scenes/RoomScene.h"
#include "ColliderComponent.h"
#include "MovementComponentFrog.h"

class PuertaComponent :public Component
{
private:
	ColliderComponent* coll = nullptr;
	void checkCollisionsTongue(Entity* ent, Collider c);

public:
	PuertaComponent() {};
	virtual ~PuertaComponent() {};
	void initComponent() override;  //Aqui inicializamos los punteros a otros componentes que vayamos a utilizar
};


