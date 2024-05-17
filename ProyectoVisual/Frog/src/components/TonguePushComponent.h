#pragma once
#include "../ecs/Component.h"
#include "../scenes/RoomScene.h"
#include "ColliderComponent.h"
#include "MovementComponentFrog.h"

class TonguePushComponent :public Component
{
private:
	int objIntID = 0;
	ColliderComponent* coll = nullptr;
	void checkCollisionsTongue(Entity* ent, Collider c);

public:
	TonguePushComponent(int id) { objIntID = id; };
	virtual ~TonguePushComponent() {};
	void initComponent() override;  //Aqui inicializamos los punteros a otros componentes que vayamos a utilizar
};


