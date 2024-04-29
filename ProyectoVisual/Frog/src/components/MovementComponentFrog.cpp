#include "MovementComponentFrog.h"
#include "../scenes/RoomScene.h"


void MovementComponentFrog::startMovement(Directions d, Vector2D v)
{
	if (!jumping && canMove) 
	{
		if (checkIfTileWalkable(tr->getCasilla() + v))
		{
			velocity = v;
			lastTimeMoved = DataManager::GetInstance()->getFrameTime();
			jumping = true;
			framesPerJump = 4 + v.magnitude() * 6; //2 frames de despegue, 3 en cada casilla, 2 de aterrizaje

		}
		actualDirection = d;

		string animation = "";
		switch (d) { //Se configura como se empieza a renderizar la lengua
		case Directions::LEFT:
			animation = "LEFT";
			break;
		case Directions::RIGHT:
			animation = "RIGHT";
			break;
		case Directions::UP:
			animation = "UP";
			break;
		case Directions::DOWN:
			animation = "DOWN";
			break;
		default:
			break;
		}
		anim->playAnimation(animation);
	}
}

void MovementComponentFrog::cancelMovement()
{
	if (jumping) {
		velocity = { 0,0 };
		lastTimeMoved = DataManager::GetInstance()->getFrameTime();
		jumping = false;
		tr->setOffset({0,0});
	}
}

void MovementComponentFrog::changeDirection(Directions d, string animation)
{
	actualDirection = d;
	anim->playAnimation("IDLE_" + animation);
}

void MovementComponentFrog::hookAttract(Vector2D newPos)
{
	startMovement(actualDirection, newPos - tr->getCasilla());
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
		tr->setCasilla(velocity + tr->getCasilla());
		std::cout << "Rana Posicion: " << "(" << tr->getCasilla().getX() << " " << tr->getCasilla().getY() << ")" << std::endl;
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

		if (framesMoved == framesPerJump) //para acabar el movimiento
		{
			tr->setCasilla(velocity + tr->getCasilla());
			tr->setOffset({ 0,0 });
			framesMoved = 0;
			jumping = false;
		}
	}
}