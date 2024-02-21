#pragma once
#include "Component.h"
/*
* Clase base abstracta del componente que gestiona el movimiento de la entidad
* 
* Cada entidad se moverá en el mapa, dependiendo únicamente de la cordenada del tile en el que 
* están colocados y no de sus coordenadas x y en la pantalla (esa interpretación se hará al renderizar)
*/
class MovementComponent : public Component
{
private:
	Vector2D<int, int> posCasilla; //Posiciones de la entidad en el tileMap

public:


};

