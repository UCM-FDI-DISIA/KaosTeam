#pragma once
#include "Component.h"
/*
* Clase base abstracta del componente que gestiona el movimiento de la entidad
* 
* Cada entidad se mover� en el mapa, dependiendo �nicamente de la cordenada del tile en el que 
* est�n colocados y no de sus coordenadas x y en la pantalla (esa interpretaci�n se har� al renderizar)
*/
class MovementComponent : public Component
{
private:
	Vector2D<int, int> posCasilla; //Posiciones de la entidad en el tileMap

public:


};

