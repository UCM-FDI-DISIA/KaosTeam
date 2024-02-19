#pragma once
/*
* Clase base de entidad para una arquitectura de componentes.
*/
#include "../utils/Vector2D.h"
#include <map>
//Enum de componentes provisional. Meted los componentes que neceisteis
enum componentsEnum
{
	MOVEMENT_COMPONENT,
	RENDER_COMPONENT,
	LIFE_COMPONENT
};
class Component;

class Entity
{
private:
	Vector2D pos;
	std::map<componentsEnum, Component*> componentes;

public:

//provisional, sentios libres de haced mas metodos, hacerlos virtuales etc
	void update();
	void Render();
	Component* getComponent(componentsEnum) const;
};

