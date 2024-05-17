#pragma once
#include "MovementComponent.h"
#include "../managers/DataManager.h"
#include "AnimationComponent.h"
#include <iostream>
using namespace std;
enum Directions
{
	UP,
	LEFT,
	RIGHT,
	DOWN,
	NONE //tonteria un poco, está aqui por si acaso
};

class MovementComponentFrog : public MovementComponent
{
private:
	InputManager* im;
	AnimationComponent* anim;
	Uint32 lastTimeMoved;
	Directions actualDirection = DOWN; //empieza mirando al frente
	
	//La idea es que este cooldown sea compartido por todos los componentes de accion de la rana como atacar y etc
	Uint32 actionCooldown = 100, movementFrameRate = 30,
		framesPerJump = 6, framesMoved = 0;
	bool jumping = false;
	bool arrastrado = false;

public:
	MovementComponentFrog(Vector2D casilla, AnimationComponent* a) : MovementComponent(), im(InputManager::GetInstance()), lastTimeMoved(SDL_GetTicks()), 
	anim(a), actualDirection(Directions::DOWN) {};
	Directions getDirection() { return actualDirection; }
	void update() override;
	bool getMoveCompleted() { return !jumping; }
	void startMovement(Directions d, Vector2D v);
	void cancelMovement();
	void changeDirection(Directions d, string animation);
	void hookAttract(Vector2D newPos);
};