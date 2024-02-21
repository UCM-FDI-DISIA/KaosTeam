#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
/*
* Clase base abstracta del componente que gestiona el movimiento de la entidad
* 
* Cada entidad se moverá en el mapa, dependiendo únicamente de la cordenada del tile en el que 
* están colocados y no de sus coordenadas x y en la pantalla (esa interpretación se hará al renderizar)
*/
class MovementComponent : public Component
{
private:
	Vector2D posCasilla; //Posiciones de la entidad en el tileMap

public:


};

