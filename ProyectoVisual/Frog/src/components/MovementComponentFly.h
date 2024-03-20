#pragma once
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "../managers/DataManager.h"
#include "../sdlutils/SDLUtils.h"
class MovementComponentFly : public MovementComponent
{
private:
	//IMPORTANTE cambiar para usar el delta time
	int waitTime = 300;
	int lastTimeMoved;
	//estados del movimiento: 0 derecha, 1 abajo, 2 izquierda, 3 arriba
	Vector2D directions[4] = { Vector2D(1, 0), Vector2D(0, 1), Vector2D(-1, 0), Vector2D(0, -1) };
	int status = 0;
	
public:
	MovementComponentFly(Vector2D pos) : MovementComponent(pos), lastTimeMoved(SDL_GetTicks()) { };
	void update() override;
};

