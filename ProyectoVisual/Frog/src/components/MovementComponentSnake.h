#pragma once
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "../managers/DataManager.h"
#include "../sdlutils/SDLUtils.h"

enum Direction {
	LEFT_ROT,
	RIGHT_ROT,
	DOWN_ROT,
	UP_ROT
};

class MovementComponentSnake : public MovementComponent {
private:
	//enum Direction { DOWN, LEFT, UP, RIGHT };
	//enum Direction { LEFT, RIGHT };
	AnimationComponent* anim;
	Uint32 coolDownTime, //Tiempo de espera entre acciones
		lastTimeAction;  //Tiempo de la ultima accion
	Direction currentDirection;
	bool isRotate, isAttack;
	int attackDistance;
	Vector2D* playerPos = nullptr;

	void rotateSnake();
	void searchFrog();
public:
	MovementComponentSnake(Vector2D pos, AnimationComponent* a) :
		MovementComponent(pos), anim(a),
		lastTimeAction(DataManager::GetInstance()->getFrameTime()), coolDownTime(1000),
		isRotate(true), isAttack(false),
		currentDirection(Direction::RIGHT_ROT), attackDistance(2) {
		//isRotate = true;  //Empieza rotando
		//isAttack = false;
		//currentDirection = DOWN;
		//coolDownTime = 1000;  
		//attackDistance = 2;
	}
	Direction getDirection() const { return currentDirection; };
	void update() override;
};

