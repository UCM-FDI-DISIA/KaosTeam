#pragma once
#include "MovementComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "AnimationComponent.h"
#include "MovementComponentFrog.h"

class TransformComponent;
class RoomScene;

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
	MovementComponentRedAnt(AnimationComponent* a, MovementComponentFrog* target) : MovementComponent(), lastTimeMoved(SDL_GetTicks()), anim(a), targetMovementComp(target), rand_(sdlutils().rand())
	{
		actualDirection = RIGHT;
		targetTransformComp = static_cast<TransformComponent*>(ent->getScene()->getPlayer()->getComponent(TRANSFORM_COMPONENT));
		playerPosition = targetTransformComp->getCasilla();
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

