#pragma once

#include "Entity.h"
/*
* Clase base abstracta a ser heredada para añadir funcionalidad a una entidad.
*/
class Component
{
	const componentsEnum ID;

public:

	virtual void initComponent();
	void setContext(Entity* ent);

	virtual void update();
	virtual void render();
	virtual void handleEvents();

protected:
	Entity* ent;
};

