#pragma once
#include "MovementComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "AnimationComponent.h"
#include "MovementComponentFrog.h"

class MovementComponentBlackAnt : public MovementComponent {
private:
	enum Direction { RIGHT, LEFT, UP, DOWN };											
	Uint32  waitTime, lastTimeMoved, movementFrameRate, //tiempo de espera (frames) para el movimiento entre casillas
		framesPerMove, framesMoved, waitTimeAttack, immobileTime;
	Direction actualDirection;		//direccion actual				
	bool isMoving;
	bool isAtacking;
	bool waitToAttack;
	bool waitToMove;
	int range;
	float diff;
	MovementComponentFrog* targetMovementComp;
	Vector2D playerPosition;
	AnimationComponent* anim;
	RandomNumberGenerator& rand_;	//generador de numeros random
	void changeDirection();
	bool isPlayerNear();
	void checkCollisionWall();
public:
	MovementComponentBlackAnt(Vector2D casilla, AnimationComponent* a, MovementComponentFrog* target) : MovementComponent(casilla), lastTimeMoved(SDL_GetTicks()), anim(a), targetMovementComp(target), rand_(sdlutils().rand())
	{
		actualDirection = RIGHT;
		playerPosition = targetMovementComp->getPosition();
		//anim->playAnimation("RIGHT");
		waitTime = 1000;
		movementFrameRate = 50;
		framesPerMove = 6;
		framesMoved = 0;
		isAtacking = false;
		isMoving = false;
		waitTimeAttack = 1000;
		immobileTime = 2000;
		range = 3;
		waitToAttack = false;
		waitToMove = false;
		diff = 0;
	};
	void update() override;
};

