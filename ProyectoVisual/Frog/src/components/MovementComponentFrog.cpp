#include "MovementComponentFrog.h"
#include "../scenes/RoomScene.h"


void MovementComponentFrog::startMovement(Directions d, Vector2D v, std::string animation)
{
	if (!jumping && checkIfTileWalkable(transform->getCasilla() + v))  //COLISIONES COMENTADAS PARA PROBAR LA TRANSICIÓON ENTRE ESCENAS
	{
		velocity = v;
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		jumping = true;
		framesPerJump = 4 + v.magnitude()*3; //2 frames de despegue, 3 en cada casilla, 2 de aterrizaje
	}

	actualDirection = d;
	anim->playAnimation(animation);
	
}

void MovementComponentFrog::changeDirection(Directions d, string animation)
{
	actualDirection = d;
	anim->playAnimation("IDLE_" + animation);
}

//CAMBIARÁ CUANDO TENGAMOS LAS COLISIONES!!!!
void MovementComponentFrog::changePosFrog(Vector2D v)
{	
	Entity* objEnDestino = ent->getScene()->getMapReader()->getTile(velocity.normalize() + transform->getCasilla())->objInTile;
	if ((objEnDestino != nullptr) && (objEnDestino->getComponent(TRANSITION_COMPONENT) != nullptr)) {
		//COLISION CON OBJETO DE TRANSICION
		static_cast<TransitionComponent*>(objEnDestino->getComponent(TRANSITION_COMPONENT))->changeMap();
	}
	else {
		//Simplemente pasa a la otra casilla
		transform->setCasilla(velocity.normalize() + transform->getCasilla());
	}
}

void MovementComponentFrog::update() {
	if (jumping && (DataManager::GetInstance()->getFrameTime() - lastTimeMoved) > movementFrameRate)
	{
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		int t = ent->getScene()->getMapReader()->getTileSize();
			
		framesMoved++;

		if (actualDirection == LEFT || actualDirection == RIGHT)
		{
			transform->setOffsetX(transform->getOffset().getX() + t / framesPerJump * velocity.getX());
			transform->setOffsetY(-t/2 * sin(3.14/framesPerJump * framesMoved)); //para calcular la altura del salto
		}
		else
		{
			transform->setOffsetY(transform->getOffset().getY() + t / framesPerJump * velocity.getY());
		}

		if (transform->getOffset().getX() * velocity.normalize().getX() >= t / 2 ||
			transform->getOffset().getY() * velocity.normalize().getY() >= t / 2) //si se mueve mas de media casilla, está en la casilla siguiente
		{
			changePosFrog(velocity.normalize() + transform->getCasilla());
			if (actualDirection == LEFT || actualDirection == RIGHT)
				transform->setOffsetX(transform->getOffset().getX() * -1);
			else
				transform->setOffsetY(transform->getOffset().getX() * -1);

		}

		if (framesMoved == framesPerJump) //para acabar el movimiento
		{
			//changePos(velocity.normalize() + posCasilla);
			transform->setOffset({ 0,0 });
			framesMoved = 0;
			jumping = false;
		}
	}
}