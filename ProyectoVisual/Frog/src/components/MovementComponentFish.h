#pragma once
#include "MovementComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "AnimationComponent.h"

class RandomNumberGenerator;
class MovementComponentFish : public MovementComponent {
private:
	enum Direction { RIGHT, LEFT };								//tiempo de espera (frames) para el movimiento entre casillas				//ultima vez en moverse
	Uint32  waitTime, lastTimeMoved, movementFrameRate,
		framesPerJump, framesMoved;
	Direction actualDirection;			//direccion actual
	int casillaSalto;				//casilla en la que debe saltar
	int casillaActual;				//casilla en la que se encuentra
	int limite;						//limite de casillas que recorre el pez (borde rio)
	RandomNumberGenerator& rand_;	//generador de numeros random
	bool isJumping;					//saber si esta saltando
	bool isMoving;
	AnimationComponent* anim;
	void changeDirection();
public:
	MovementComponentFish(Vector2D casilla, int boundX, AnimationComponent* a) : MovementComponent(casilla), lastTimeMoved(SDL_GetTicks()), limite(boundX),anim(a), rand_(sdlutils().rand())
	{
		casillaSalto = rand_.nextInt(0, boundX - 1); //elegir aleatoriamente la casilla en la que va a saltar
		actualDirection = RIGHT;
		anim->playAnimation("RIGHT");
		casillaActual = 0;
		waitTime = 1000;
		movementFrameRate = 50;
		framesPerJump = 6;
		framesMoved = 0;
		isJumping = false;
		isMoving = false;
	};
	void update() override;
};

