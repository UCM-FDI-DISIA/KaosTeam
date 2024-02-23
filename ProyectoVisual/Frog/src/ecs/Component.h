#pragma once

#include "../utils/Vector2D.h"
#include "Entity.h"
/*
* Clase base abstracta a ser heredada para a�adir funcionalidad a una entidad.
*/
class Component
{ 
	componentsEnum ID;

public:
	Component();
	virtual ~Component() {};

	virtual void initComponent() {};
	void setContext(Entity* ent);

	virtual void update() {};

protected:
	Entity* ent;
};

