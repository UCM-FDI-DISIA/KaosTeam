#pragma once
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "../managers/DataManager.h"
#include "../sdlutils/SDLUtils.h"

class MovementComponentSnake : public MovementComponent {
private:
	enum Direction { DOWN, LEFT, UP, RIGHT };
	Uint32 coolDownTime, //Tiempo de espera entre acciones
		lastTimeAction;  //
	Direction currentDirection;
	bool isRotate, isAttack;
	AnimationComponent* anim;
	void rotateSnake();
public:
	MovementComponentSnake(Vector2D pos, AnimationComponent* a) :
		MovementComponent(pos), lastTimeAction(DataManager::GetInstance()->getFrameTime()), anim(a) {
		isRotate = true;  //
		isAttack = false;
		currentDirection = DOWN;
		coolDownTime = 10000;  

	};
	void update() override;


};

