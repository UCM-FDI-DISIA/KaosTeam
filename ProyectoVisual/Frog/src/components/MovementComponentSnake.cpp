#include "MovementComponentSnake.h"



void MovementComponentSnake::update()
{
	if (DataManager::GetInstance()->getFrameTime() - lastTimeAction > coolDownTime); {

		lastTimeAction = DataManager::GetInstance()->getFrameTime(); //Actualizamos tiempo de acci�n

		//La serpeinte va a estar rotando constantemente
		//... L�gica de rotaci�n aqu�
		//Primero comprobamos si est� rotando la serpiente o no
		if (isRotate)
			rotateSnake();




		//En el momento que la rana este en el �rea de visi�n la serpiente ataca
		// desactivamos rotaci�n y activamos ataque


		//Estiramos serpiente hasta la posici�n de la rana y atacamos

		//Vuelve a su posicion original y desactivamos ataque
	}

}

void MovementComponentSnake::rotateSnake() {
	//Cambiamos direcci�n de rotaci�n
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
