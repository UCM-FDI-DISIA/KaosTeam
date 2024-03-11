#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../managers/InputManager.h"

/*
* Clase base abstracta del componente que gestiona el movimiento de la entidad
* 
* Cada entidad se moverá en el mapa, dependiendo únicamente de la cordenada del tile en el que 
* están colocados y no de sus coordenadas x y en la pantalla (esa interpretación se hará al renderizar)
*/
class MovementComponent : public Component
{
protected:
	Vector2D posCasilla = {0,0}; //Posiciones de la entidad en el tileMap
	Vector2D destCasilla = {0,0}; //La casilla destino a la que se tiene que mover
	Vector2D offsetInCasilla = Vector2D(0,0);
	int boundX = 0;
	int boundY = 0;
public:
	MovementComponent() { };
	MovementComponent(Vector2D casilla) : posCasilla(casilla), destCasilla(casilla) { };
	Vector2D getPosition();
	Vector2D getOffset() { return offsetInCasilla; }
	void setBoundX(int newBoundX) { boundX = newBoundX; }
	void setBoundY(int newBoundY) { boundY = newBoundY; }
};

