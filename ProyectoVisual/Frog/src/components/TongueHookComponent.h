#pragma once
#include "../ecs/Component.h"
#include "ColliderComponent.h"
#include "MovementComponentFrog.h"
#include "AttackComponentFrog.h"

class TongueHookComponent :public Component
{
private:
	ColliderComponent* coll = nullptr;
	void checkCollisionsTongue(Entity* _ent, Collider c);

public:
	TongueHookComponent() {};
	virtual ~TongueHookComponent() {};
	void initComponent() override;  //Aqui inicializamos los punteros a otros componentes que vayamos a utilizar
};


