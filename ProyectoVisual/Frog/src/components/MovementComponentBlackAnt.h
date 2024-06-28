#pragma once
#include "MovementComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "AnimationComponent.h"
#include "MovementComponentFrog.h"

/*
* Clase que gestiona el comportamiendo de la hormiga negra
* -la direccion en la que se tiene que mover
* -comprueba si la rana esta cerca para atacarla
* -comprueba que despues del ataque no se haya chocado con una pared, si es asi se queda inmovil por un tiempo
*/

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
	RandomNumberGenerator& rand_;	//generador de numeros random

	void changeDirection();
	bool isPlayerNear();
	void checkCollisionWall();
public:
	MovementComponentBlackAnt(AnimationComponent* a);
	~MovementComponentBlackAnt();
	void update() override;
	void initComponent() override;
};