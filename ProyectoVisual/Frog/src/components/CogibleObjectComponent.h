#pragma once
#include "../ecs/Component.h"
/*Comportamiento de un objeto(entidad) con el que el jugador puede interactuar con la lengua,
Al hacerlo obtiene un efecto ya sea temporal o permanente.
Ej. Se le añade vida, se le aumenta el daño, obtiene dinero, etc*/
class Collider;
class CogibleObjectComponent : public Component
{
public:
	void initComponent() override;
	CogibleObjectComponent();
private:
	void checkHit(Entity* e, Collider c);
	void PickUpItem();
	//La cantidad de item a incrementar
	int itemAmmount;
};

