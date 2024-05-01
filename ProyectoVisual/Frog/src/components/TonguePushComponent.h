#pragma once
#include "../ecs/Component.h"
#include "ColliderComponent.h"
#include "MovementComponentFrog.h"

class TonguePushComponent :public Component
{
private:
	ColliderComponent* coll = nullptr;
	void checkCollisionsTongue(Entity* ent, Collider c);

public:
	TonguePushComponent() {};
	virtual ~TonguePushComponent() {};
	void initComponent() override;  //Aqui inicializamos los punteros a otros componentes que vayamos a utilizar
};


