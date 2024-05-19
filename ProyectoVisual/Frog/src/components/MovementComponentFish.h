#pragma once
#include "MovementComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "AnimationComponent.h"
/*
* Clase que gestiona el comportamiendo del pez
* -la direccion en la que se tiene que mover
* -cuando tiene que cambiar de direccion
* -durante su camino salta en una casilla elegida de forma aleatoria
*/
class RandomNumberGenerator;
class MovementComponentFish : public MovementComponent {
private:
	enum Direction { RIGHT, LEFT };								//tiempo de espera (frames) para el movimiento entre casillas				//ultima vez en moverse
	Uint32  waitTime, lastTimeMoved, movementFrameRate,
		framesPerMove, framesMoved;
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
	MovementComponentFish(int boundX, AnimationComponent* a);
	~MovementComponentFish();
	void update() override;
	void initComponent() override;
};

