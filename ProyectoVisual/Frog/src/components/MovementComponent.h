#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../managers/InputManager.h"

/*
* Clase base abstracta del componente que gestiona el movimiento de la entidad
* 
* Cada entidad se mover� en el mapa, dependiendo �nicamente de la cordenada del tile en el que 
* est�n colocados y no de sus coordenadas x y en la pantalla (esa interpretaci�n se har� al renderizar)
*/
class MovementComponent : public Component
{
protected:
	Vector2D posCasilla = {0,0}; //Posiciones de la entidad en el tileMap
	Vector2D velocity = {0,0}; //La velocidad (numero de casillas) q se tiene q mover
	Vector2D offsetInCasilla = Vector2D(0,0);

	int boundX = 0;
	int boundY = 0;

public:
	MovementComponent() { };
	MovementComponent(Vector2D casilla);
	Vector2D getPosition();
	Vector2D* getPosPointer() { return &posCasilla; };
	Vector2D getOffset() { return offsetInCasilla; }

	//importante!! usad este metodo para cambiar de casilla!!
	void changePos(Vector2D v);
	void resetPos(Vector2D v);
	void initComponent() override;

	void setBoundX(int newBoundX) { boundX = newBoundX; }
	void setBoundY(int newBoundY) { boundY = newBoundY; }
	bool checkIfTileWalkable(Vector2D);
};

