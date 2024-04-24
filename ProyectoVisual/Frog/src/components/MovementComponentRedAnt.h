#pragma once
#include "MovementComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "AnimationComponent.h"
#include "MovementComponentFrog.h"
#include "TransformComponent.h"

class MovementComponentRedAnt : public MovementComponent {
private:
	enum Direction { RIGHT, LEFT, UP, DOWN };
	Uint32  waitTime, lastTimeMoved, movementFrameRate, //tiempo de espera (frames) para el movimiento entre casillas
		framesPerMove, framesMoved;
	Direction actualDirection;		//direccion actual				
	bool isMoving;
	bool escape;
	int range;
	//MovementComponentFrog* targetMovementComp;
	TransformComponent* targetTransformComp;
	Vector2D playerPosition;
	AnimationComponent* anim;
	RandomNumberGenerator& rand_;	//generador de numeros random
	void changeDirection();
	void isPlayerNear();
	void canMove(Vector2D vel, Direction dir);
public:
	MovementComponentRedAnt(AnimationComponent* a, MovementComponentFrog* target);
	~MovementComponentRedAnt() {};
	void update() override;
	void initComponent() override; 
};

