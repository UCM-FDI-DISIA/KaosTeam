#include "MovementComponentSnake.h"



void MovementComponentSnake::update()
{
	if (DataManager::GetInstance()->getFrameTime() - lastTimeAction > coolDownTime); {

		lastTimeAction = DataManager::GetInstance()->getFrameTime(); //Actualizamos tiempo de acción

		//La serpeinte va a estar rotando constantemente
		//... Lógica de rotación aquí
		//Primero comprobamos si está rotando la serpiente o no
		if (isRotate)
			rotateSnake();




		//En el momento que la rana este en el área de visión la serpiente ataca
		// desactivamos rotación y activamos ataque


		//Estiramos serpiente hasta la posición de la rana y atacamos

		//Vuelve a su posicion original y desactivamos ataque
	}

}

void MovementComponentSnake::rotateSnake() {
	//Cambiamos dirección de rotación
	switch (currentDirection) {
	case DOWN:
		currentDirection = LEFT;
		anim->playAnimation("LEFT_ROTATION");
		break;
	case LEFT:
		currentDirection = UP;
		anim->playAnimation("UP_ROTATION");
		break;
	case UP:
		currentDirection = RIGHT;
		anim->playAnimation("RIGHT_ROTATION");
		break;
	case RIGHT:
		currentDirection = DOWN;
		anim->playAnimation("DOWN_ROTATION");
		break;
	}
}
