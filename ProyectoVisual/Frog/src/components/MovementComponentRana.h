#pragma once
#include "MovementComponent.h";

class MovementComponentRana : public MovementComponent
{
private:
	InputManager* im;
	Uint32 lastTimeMoved;
	//La idea es que este cooldown sea compartido por todos los componentes de accion de la rana como atacar y etc
	Uint32 actionCooldown;
public:
	MovementComponentRana(Vector2D casilla) : MovementComponent(casilla), im(InputManager::GetInstance()) { actionCooldown = 100; };
	void update() override;
};