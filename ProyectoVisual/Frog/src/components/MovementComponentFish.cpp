#include "MovementComponentFish.h"
#include "../sdlutils/RandomNumberGenerator.h"

void MovementComponentFish::update() {
	if ((DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > waitTime)
	{
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		//si la casilla actual es donde debe saltar
		if (casillaActual == casillaSalto) {
			switch (actualDirection)
			{
			//se mueve media casilla hacia arriba y media casilla hacia abajo en la direccion correspondiente
			//cuando ha terminado de saltar es cuando termina el movimiento completo (casillaActual++)
			case RIGHT:
				if (!isJumping) {
					isJumping = true;
					posCasilla = posCasilla + Vector2D(0.5, -1);
					
				}
				else if (isJumping) {
					isJumping = false;
					posCasilla = posCasilla + Vector2D(0.5, 1);
					casillaActual++;
				}
				
				break;
			case LEFT:
				if (!isJumping) {
					isJumping = true;
					posCasilla = posCasilla + Vector2D(-0.5, -1);
				}
				else if (isJumping) {
					isJumping = false;
					posCasilla = posCasilla + Vector2D(-0.5, 1);
					casillaActual++;
				}
				break;
			default:
				break;
			}
		}
		else {
			//se mueve una casilla en la direccion correspondiente
			switch (actualDirection)
			{
			case RIGHT:
				posCasilla = posCasilla + Vector2D(1, 0);
				break;
			case LEFT:
				posCasilla = posCasilla + Vector2D(-1, 0);
				break;
			default:
				break;
			}
			casillaActual++;
		}
		
		//si la casilla en la que se encuentra es la del borde (-1 pq se empieza a contar en 0) 
		//se cambia de direccion
		if (casillaActual == limite - 1) changeDirection();
	}
}
//metodo para cambiar de direccion y todo lo que conlleva eso
void MovementComponentFish::changeDirection() {
	//cambiar direccion
	if (actualDirection == RIGHT) actualDirection = LEFT;
	else if (actualDirection == LEFT) actualDirection = RIGHT;
	//restaurar la casilla actual a 0
	casillaActual = 0;
	//volver a elegir aleatoriamente la casilla en la que va a saltar
	casillaSalto = rand_.nextInt(0, limite - 1);
}