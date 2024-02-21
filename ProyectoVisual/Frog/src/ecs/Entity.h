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
	LIFE_COMPONENT,
};
class Component;
class RenderComponent;

class Entity
{
private:
	Vector2D pos;
	std::map<componentsEnum, Component*> componentes;
	RenderComponent* renderComponent; //el render no tiene update, y solo se le llama para hacer el render, osea q aqui va

public:
//provisional, sentios libres de haced mas metodos, hacerlos virtuales etc
	Entity(int, int);
	void addComponent(componentsEnum, Component*);
	~Entity();
	void update();
	void render();
	Component* getComponent(componentsEnum) const;
};

