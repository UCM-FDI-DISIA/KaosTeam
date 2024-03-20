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
class MovementComponentFrog : public MovementComponent
{
private:
	InputManager* im;
	Uint32 lastTimeMoved;
	Directions actualDirection = DOWN; //empieza mirando al frente

	//La idea es que este cooldown sea compartido por todos los componentes de accion de la rana como atacar y etc
	Uint32 actionCooldown = 100, movementFrameRate = 50,
		framesPerJump = 6, framesMoved = 0;
	bool jumping = false;
	void startMovement(Directions, Vector2D);

public:
	MovementComponentFrog(Vector2D casilla) : MovementComponent(casilla), im(InputManager::GetInstance()), lastTimeMoved(SDL_GetTicks()) {};
	Directions getDirection() { return actualDirection; }
	void update() override;
	bool getMoveCompleted() { return !jumping; }
};