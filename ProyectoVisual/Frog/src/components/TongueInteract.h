#pragma once
#include "../ecs/Component.h"
#include "ColliderComponent.h"

class TongueInteract :public Component
{
private:
	ColliderComponent* coll = nullptr;
	void checkCollisionsTongue(Entity* ent, Collider c);

public:
	TongueInteract() {};
	virtual ~TongueInteract() {};
	void initComponent() override;  //Aqui inicializamos los punteros a otros componentes que vayamos a utilizar
};


