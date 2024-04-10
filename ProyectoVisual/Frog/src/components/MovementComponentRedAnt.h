#pragma once
#include "MovementComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "AnimationComponent.h"
#include "MovementComponentFrog.h"


class MovementComponentRedAnt : public MovementComponent {
private:
	enum Direction { RIGHT, LEFT, UP, DOWN };
	Uint32  waitTime, lastTimeMoved, movementFrameRate, //tiempo de espera (frames) para el movimiento entre casillas
		framesPerMove, framesMoved;
	Direction actualDirection;		//direccion actual				
	bool isMoving;
	bool escape;
	int range;
	MovementComponentFrog* targetMovementComp;
	Vector2D playerPosition;
	AnimationComponent* anim;
	RandomNumberGenerator& rand_;	//generador de numeros random
	void changeDirection();
	void isPlayerNear();
	void canMove(Vector2D vel, Direction dir);
public:
	MovementComponentRedAnt(Vector2D casilla, AnimationComponent* a, MovementComponentFrog* target) : MovementComponent(casilla), lastTimeMoved(SDL_GetTicks()), anim(a), targetMovementComp(target), rand_(sdlutils().rand())
	{
		actualDirection = RIGHT;
		playerPosition = targetMovementComp->getPosition();
		//anim->playAnimation("RIGHT");
		waitTime = 500;
		movementFrameRate = 30;
		framesPerMove = 6;
		framesMoved = 0;
		isMoving = false;
		escape = false;
		range = 2;
	};
	void update() override;
};

