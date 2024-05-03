#pragma once
#include "../ecs/Component.h"
/*Comportamiento de un objeto(entidad) con el que el jugador puede interactuar con la lengua,
Al hacerlo obtiene un efecto ya sea temporal o permanente.
Ej. Se le a�ade vida, se le aumenta el da�o, obtiene dinero, etc*/
class Collider;
class CogibleObjectComponent : public Component
{
	void checkHit(Entity* e, Collider c);
	void initComponent() override;
};

