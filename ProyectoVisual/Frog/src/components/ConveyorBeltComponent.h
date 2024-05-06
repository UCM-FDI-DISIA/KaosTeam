#pragma once
#include "../ecs/Component.h"


class ConveyorBeltComponent :public Component
{
private:
	const int CoolDown = 1000;	//Cooldown antes de moverse
	int direccion;				//Direccion en la que se mueven los objetos: Norte 0, este 1, sur 2 y oeste 3
	Vector2D position;			//Posici�n para poder mover los objetos adonde sea (quiz�s se elimine)

public:
	ConveyorBeltComponent(int direccion, Vector2D pos);

};

