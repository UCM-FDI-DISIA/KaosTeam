#pragma once
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "../managers/DataManager.h"
#include "../sdlutils/SDLUtils.h"

class TransformComponent;

enum Direction {
	LEFT_ROT,
	RIGHT_ROT,
	DOWN_ROT,
	UP_ROT
};

class MovementComponentSnake : public MovementComponent {
private:
	AnimationComponent* anim;
	Uint32 coolDownTime, //Tiempo de espera entre acciones
		lastTimeAction;  //Tiempo de la ultima accion
	Direction currentDirection;
	bool isRotate, isAttack;
	int attackDistance;
	TransformComponent* targetTransformComp;
	Vector2D playerPos;

	void rotateSnake();
	void searchFrog();
public:
	MovementComponentSnake(AnimationComponent* a);
		
	Direction getDirection() const { return currentDirection; };
	void update() override;
};

