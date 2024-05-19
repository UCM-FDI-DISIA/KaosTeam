#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
/*Comportamiento de un objeto(entidad) con el que el jugador puede interactuar con la lengua,
Al hacerlo obtiene un efecto ya sea temporal o permanente.
Ej. Se le añade vida, se le aumenta el daño, obtiene dinero, etc*/
enum Items;
class Collider;
class CogibleObjectComponent : public Component
{
public:
	CogibleObjectComponent();
	virtual ~CogibleObjectComponent();
	void initComponent() override;
	CogibleObjectComponent(Items);
	CogibleObjectComponent(Items, int);
	void update() override;
private:
	void checkHit(Entity* e, Collider c);
	void PickUpItem();
	//La cantidad de item a incrementar
	int itemAmmount;
	//El item que guarda el objeto
	Items item;
	bool hitted;
	Uint32 elapsedTime;
	const Uint32 WAIT_PICK = 1000;
};

