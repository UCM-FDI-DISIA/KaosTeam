#pragma once
#include "MovementComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "AnimationComponent.h"

class MovementComponentBlackAnt : public MovementComponent {
private:
	enum Direction { RIGHT, LEFT, UP, DOWN };											
	Uint32  waitTime, lastTimeMoved, movementFrameRate, //tiempo de espera (frames) para el movimiento entre casillas
		framesPerMove, framesMoved, waitTimeAttack, immobileTime;
	Direction actualDirection;		//direccion actual				
	//int casillaActual;				//casilla en la que se encuentra
	bool isMoving;
	bool isAtacking;
	bool waitToAttack;
	bool waitToMove;
	int range;
	Vector2D playerPosition;
	AnimationComponent* anim;
	RandomNumberGenerator& rand_;	//generador de numeros random
	void changeDirection();
	void isPlayerNear();
	void checkCollisionWall();
public:
	MovementComponentBlackAnt(Vector2D casilla, AnimationComponent* a, Vector2D playerPos) : MovementComponent(casilla), lastTimeMoved(SDL_GetTicks()), anim(a), playerPosition(playerPos), rand_(sdlutils().rand())
	{
		actualDirection = RIGHT;
		anim->playAnimation("RIGHT");
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
	};
	void update() override;
};

