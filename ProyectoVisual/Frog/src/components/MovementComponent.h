#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
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

public:
	MovementComponent() {};
	MovementComponent(Vector2D casilla);
	Vector2D getCasilla();
};

