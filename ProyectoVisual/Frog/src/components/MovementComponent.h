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
	Vector2D velocity = {0,0}; //La velocidad (numero de casillas) q se tiene q mover

	int boundX = 0;
	int boundY = 0;

	TransformComponent* tr = nullptr;
public:
	MovementComponent() {};
	void initComponent() override;

	void setBoundX(int newBoundX) { boundX = newBoundX; }
	void setBoundY(int newBoundY) { boundY = newBoundY; }
	bool checkIfTileWalkable(Vector2D);
};

