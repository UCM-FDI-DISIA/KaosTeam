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
	TransformComponent* targetTransformComp;
	Vector2D playerPosition;
	AnimationComponent* anim;
	TransformComponent* tr;
	RandomNumberGenerator& rand_;	//generador de numeros random
	void changeDirection();
	bool isPlayerNear();
	void checkCollisionWall();
public:
	MovementComponentBlackAnt(Vector2D casilla, AnimationComponent* a) : MovementComponent(), lastTimeMoved(SDL_GetTicks()), anim(a), rand_(sdlutils().rand())
	{
		tr = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
		actualDirection = RIGHT;
		playerPosition = targetTransformComp->getCasilla();
		//anim->playAnimation("RIGHT");
		waitTime =500;
		movementFrameRate = 30;
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

