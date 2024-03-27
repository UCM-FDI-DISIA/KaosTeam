#pragma once
#include "../ecs/Component.h"
//No lo tengo muy claro pero supongo que a la hora de colisionar con la lengua de Flonk, esta será destruida y
//llamará al game para spawnear una nueva entidad 
//Tendremos un Enum que va a determinar qué objeto va a spawnear

//También podriamos hacer que en lugar de spawnear objetos, esto cubran objetos ya spawneados, o sea, que si
//un item y una vsija estan en la misma casilla, pues que el objeto esté desactivado
enum item {
	EMPTY
};
class ObjectBreakableJarComponent:public Component
{
private:
public:
};