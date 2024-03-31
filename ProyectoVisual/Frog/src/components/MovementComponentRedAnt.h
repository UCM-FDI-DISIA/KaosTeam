#pragma once
#include "MovementComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "AnimationComponent.h"

class MovementComponentRedAnt : public MovementComponent {
private:
	enum Direction { RIGHT, LEFT, UP, DOWN };
	Uint32  waitTime, lastTimeMoved, movementFrameRate, //tiempo de espera (frames) para el movimiento entre casillas
		framesPerMove, framesMoved;
	Direction actualDirection;		//direccion actual				
	bool isMoving;
	bool escape;
	int range;
	Vector2D playerPosition;
	AnimationComponent* anim;
	RandomNumberGenerator& rand_;	//generador de numeros random
	void changeDirection();
	void isPlayerNear();
public:
	MovementComponentRedAnt(Vector2D casilla, AnimationComponent* a, Vector2D playerPos) : MovementComponent(casilla), lastTimeMoved(SDL_GetTicks()), anim(a), playerPosition(playerPos), rand_(sdlutils().rand())
	{
		actualDirection = RIGHT;
		//anim->playAnimation("RIGHT");
		waitTime = 1000;
		movementFrameRate = 50;
		framesPerMove = 6;
		framesMoved = 0;
		isMoving = false;
		escape = 1000;
		range = 3;
	};
	void update() override;
};

