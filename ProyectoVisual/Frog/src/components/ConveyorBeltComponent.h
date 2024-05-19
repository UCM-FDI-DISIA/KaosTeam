#pragma once
#include "../ecs/Component.h"
#include "../scenes/RoomScene.h"
#include "ColliderComponent.h"

enum DirectionConveyorEnum { NORTE, ESTE, SUR, OESTE };

class ConveyorBeltComponent :public Component
{
private:
	const int COOLDOWN = 1000;			//Cooldown antes de moverse
	int direction;						//Direccion en la que se mueven los objetos: Norte 0, este 1, sur 2 y oeste 3
	Vector2D position;					//Posición para poder mover los objetos adonde sea
	
	ColliderComponent* coll = nullptr;	//Referencias
	RoomScene* scen = nullptr;

	void CheckCollisionsBelt(Entity* ent, Collider c);

public:
	ConveyorBeltComponent(int direccion, Vector2D pos);
	void initComponent() override;
};

