#pragma once
#include "MovementComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "AnimationComponent.h"
#include "TransformComponent.h"

/*
* Clase que gestiona el comportamiendo de la cucaracha
* -la direccion en la que se tiene que mover
*/

class MovementComponentCockroach : public MovementComponent {
private:
	enum Direction { RIGHT, LEFT, UP, DOWN };
	Uint32  waitTime, lastTimeMoved, movementFrameRate, //tiempo de espera (frames) para el movimiento entre casillas
		framesPerMove, framesMoved;
	Direction actualDirection;		//direccion actual				
	bool isMoving;
	bool isAttacked;
	AnimationComponent* anim;
	RandomNumberGenerator& rand_;
	void changeDirection();
public:
	MovementComponentCockroach(AnimationComponent* a);
	~MovementComponentCockroach();
	void update() override;
	void initComponent() override;
};