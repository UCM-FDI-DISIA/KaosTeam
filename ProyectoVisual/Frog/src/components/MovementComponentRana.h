#pragma once
#include "MovementComponent.h";

class MovementComponentRana : public MovementComponent
{
private:
	InputManager* im;
public:
	MovementComponentRana(Vector2D casilla) : MovementComponent(casilla), im(InputManager::GetInstance()) {};
	void update() override;
};

