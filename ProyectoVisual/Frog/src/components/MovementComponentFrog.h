#pragma once
#include "MovementComponent.h";
#include "../managers/DataManager.h"
enum Directions
{
	UP,
	LEFT,
	RIGHT,
	DOWN
};
class MovementComponentFrog: public MovementComponent
{
private:
	InputManager* im;
	Uint32 lastTimeMoved;
	Directions actualDirection;
	
	//La idea es que este cooldown sea compartido por todos los componentes de accion de la rana como atacar y etc
	Uint32 actionCooldown, movementFrameRate = 50, 
		framesPerJump = 5, framesMoved = 0;
	bool jumping = false;
	bool movementCompleted = false;
public:
	MovementComponentFrog(Vector2D casilla) : MovementComponent(casilla), im(InputManager::GetInstance()), lastTimeMoved(SDL_GetTicks()) { actionCooldown = 100; };
	Directions getDirection() { return actualDirection; }
	void update() override;
	bool getIsMoving() { return jumping; }
	bool getMovementCompleted() { return movementCompleted; }
};