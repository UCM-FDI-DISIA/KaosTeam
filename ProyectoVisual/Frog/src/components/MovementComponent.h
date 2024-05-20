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
class TransformComponent;
class MovementComponent : public Component
{
protected:
	Vector2D velocity = { 0,0 }; //La velocidad (numero de casillas) q se tiene q mover

	int boundX = 0;
	int boundY = 0;

	bool canMove;  //Booleano que indica si se puede mover o no (si la entidad muere, esto impide que se mueva) por defecto es true

	TransformComponent* tr = nullptr;
public:
	MovementComponent() : canMove(true) {};
	void initComponent() override;

	//Getters
	//Para comprobar q la tile existe
	bool checkIfTileWalkable(Vector2D v) const;

	//Setters
	void setBoundX(int newBoundX) { boundX = newBoundX; }
	void setBoundY(int newBoundY) { boundY = newBoundY; }
	void setCanMove(bool b) { canMove = b; };
	bool getMoveState() const { return canMove; };
	bool checkIfTileWalkable(Vector2D);
};

