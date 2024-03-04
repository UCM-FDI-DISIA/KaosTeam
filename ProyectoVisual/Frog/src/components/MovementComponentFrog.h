#pragma once
#include "MovementComponent.h";
#include "../managers/DataManager.h"
class MovementComponentFrog: public MovementComponent
{
private:
	InputManager* im;
	Uint32 lastTimeMoved;
	//La idea es que este cooldown sea compartido por todos los componentes de accion de la rana como atacar y etc
	Uint32 actionCooldown;
public:
	MovementComponentFrog(Vector2D casilla) : MovementComponent(casilla), im(InputManager::GetInstance()), lastTimeMoved(SDL_GetTicks()) { actionCooldown = 100; };
	void update() override;
};