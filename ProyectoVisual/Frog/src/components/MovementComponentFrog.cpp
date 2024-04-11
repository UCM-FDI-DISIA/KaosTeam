#include "MovementComponentFrog.h"
#include "../scenes/RoomScene.h"


void MovementComponentFrog::startMovement(Directions d, Vector2D v, std::string animation)
{
	if (!jumping) 
	{
		if (checkIfTileWalkable(tr->getCasilla() + velocity))
		{
			velocity = v;
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			jumping = true;
			framesPerJump = 4 + v.magnitude() * 6; //2 frames de despegue, 3 en cada casilla, 2 de aterrizaje

		}
		actualDirection = d;
		anim->playAnimation(animation);
	}
}

void MovementComponentFrog::changeDirection(Directions d, string animation)
{
	actualDirection = d;
	anim->playAnimation("IDLE_" + animation);
}

//CAMBIARÁ CUANDO TENGAMOS LAS COLISIONES!!!!
void MovementComponentFrog::changePosFrog(Vector2D v)
{	
	Entity* objEnDestino = ent->getScene()->getMapReader()->getTile(velocity.normalize() + tr->getCasilla())->objInTile;
	if ((objEnDestino != nullptr) && (objEnDestino->getComponent(TRANSITION_COMPONENT) != nullptr)) {
		//COLISION CON OBJETO DE TRANSICION
		static_cast<TransitionComponent*>(objEnDestino->getComponent(TRANSITION_COMPONENT))->changeMap();
	}
	else {
		//Simplemente pasa a la otra casilla
		tr->setCasilla(velocity.normalize() + tr->getCasilla());
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
			tr->setOffsetX(tr->getOffset().getX() + t / framesPerJump * velocity.getX());
			tr->setOffsetY(-t/2 * sin(3.14/framesPerJump * framesMoved)); //para calcular la altura del salto
		}
		else
		{
			tr->setOffsetY(tr->getOffset().getY() + t / framesPerJump * velocity.getY());
		}

		//como las colisiones ya no se hacen por casillas, esto no lo necesitamos

		//if (tr->getOffset().getX() * velocity.normalize().getX() >= t / 2 ||
		//	tr->getOffset().getY() * velocity.normalize().getY() >= t / 2) //si se mueve mas de media casilla, está en la casilla siguiente
		//{
		//	//este chikiparrafo cambiará cuando tengamos las colisones
		//	if (checkIfTileWalkable(velocity.normalize() + tr->getCasilla()))
		//		changePosFrog(velocity.normalize() + tr->getCasilla());
		//	else
		//		tr->getCasilla() = velocity.normalize() + tr->getCasilla();


		//	if (actualDirection == LEFT || actualDirection == RIGHT)
		//		tr->getOffset().setX(tr->getOffset().getX() * -1);
		//	else
		//		tr->getOffset().setY(tr->getOffset().getY() * -1);

		//}

		if (framesMoved == framesPerJump) //para acabar el movimiento
		{
			changePosFrog(velocity + tr->getCasilla());
			//changePos(velocity.normalize() + posCasilla);
			tr->setOffset({ 0,0 });
			framesMoved = 0;
			jumping = false;
		}
	}
}