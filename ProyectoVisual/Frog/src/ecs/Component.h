#pragma once

#include "../utils/Vector2D.h"
#include "Entity.h"

/*
* Clase base abstracta a ser heredada para a�adir funcionalidad a una entidad.
*/
class Component
{ 
	//El tipo del componente. Se usa para guardar y encontrar en el mapa de componentes de la entidad.
	ComponentsEnum ID;
public:
	Component();
	virtual ~Component() {};

	/*A ser llamado por el gestor de creación de entidades y componentes después de construir el objeto.
	Su objetivo es llevar a cabo inicializaciones que sólo se pueden hacer después de la construcción*/
	virtual void initComponent() {};
	//Establece la entidad que posee este componente.
	void setContext(Entity* ent);
	//A ser llamado por la entidad en cada frame.
	virtual void update() {};
protected:
	//La entidad que posee este componente
	Entity* ent;
};

