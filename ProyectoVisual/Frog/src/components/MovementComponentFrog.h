#pragma once
#include "MovementComponent.h";
#include "../managers/DataManager.h"
#include "AnimationComponent.h"
#include <iostream>
enum Directions
{
	UP,
	LEFT,
	RIGHT,
	DOWN
};
class MovementComponentFrog : public MovementComponent
{
private:
	InputManager* im;
	AnimationComponent* anim;
	Uint32 lastTimeMoved;
	Directions actualDirection = DOWN; //empieza mirando al frente

	//La idea es que este cooldown sea compartido por todos los componentes de accion de la rana como atacar y etc
	Uint32 actionCooldown = 100, movementFrameRate = 50,
		framesPerJump = 6, framesMoved = 0;
	bool jumping = false;
	

public:
	MovementComponentFrog(Vector2D casilla, AnimationComponent* a) : MovementComponent(casilla), im(InputManager::GetInstance()), lastTimeMoved(SDL_GetTicks()), 
	anim(a), actualDirection(Directions::DOWN) {};
	Directions getDirection() { return actualDirection; }
	void update() override;
	bool getMoveCompleted() { return !jumping; }
	void startMovement(Directions d, Vector2D v, std::string animation);
};