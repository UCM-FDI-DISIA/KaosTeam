#pragma once
#include "MovementComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"



class RandomNumberGenerator;
class MovementComponentFish : public MovementComponent {
private:
	enum Direction { RIGHT, LEFT };
	int waitTime;					//tiempo de espera (frames) para el movimiento entre casillas
	int lastTimeMoved;				//ultima vez en moverse
	Direction actualDirection;			//direccion actual
	int casillaSalto;				//casilla en la que debe saltar
	int casillaActual;				//casilla en la que se encuentra
	int limite;						//limite de casillas que recorre el pez (borde rio)
	RandomNumberGenerator& rand_;	//generador de numeros random
	bool isJumping;					//saber si esta saltando
	void changeDirection();			
public:
	MovementComponentFish(Vector2D pos, int boundX) : MovementComponent(pos), lastTimeMoved(SDL_GetTicks()), limite(boundX), rand_(sdlutils().rand()) 
	{
		casillaSalto = rand_.nextInt(0, boundX-1); //elegir aleatoriamente la casilla en la que va a saltar
		actualDirection = RIGHT;
		casillaActual = 0;
		waitTime = 750;
		isJumping = false;
	};
	void update() override;
};
