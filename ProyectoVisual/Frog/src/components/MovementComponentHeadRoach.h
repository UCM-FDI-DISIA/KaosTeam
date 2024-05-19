#pragma once
#include "MovementComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "TransformComponent.h"
#include "MovementComponentFrog.h"
#include "ColliderComponent.h"
#include "../sdlutils/VirtualTimer.h"

/*
* Clase que gestiona el comportamiendo de la cucaracha
* -solo se mueve cuando se crea cuando se quiere lanzar, al morir la cucaracha se queda quieta
* -la direccion en la que se tiene que mover
* -colision de la cabeza contra enemigos
*/

class MovementComponentHeadRoach : public MovementComponent {
private:
	Directions direction;
	bool canMove;
	bool hitted;
	Vector2D velocity = Vector2D(0, 0);
	
	MovementComponentFrog* moveFrog = nullptr; //para acceder a la direcci�n a la que mira FLonk en ese instante
	TransformComponent* tr = nullptr;
	ColliderComponent* coll = nullptr;
	VirtualTimer timerForDelete;
	const Uint32 WAIT_DELETE = 2000;
	void moveHead();
	void checkCanMove(Vector2D vel);
	void checkEntityCollisions(Entity* ent, Collider c);

public:
	MovementComponentHeadRoach(bool move);
	~MovementComponentHeadRoach();
	void update() override;
	void initComponent() override;
};