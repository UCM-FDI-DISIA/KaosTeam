#pragma once
/*
* Clase base de entidad para una arquitectura de componentes.
*/
#include <map>
//Enum de componentes provisional. Meted los componentes que neceisteis
enum componentsEnum
{
	MOVEMENT_COMPONENT,
	LIFE_COMPONENT,
	RENDER_COMPONENT,
};
class Component;
class RenderComponent;
class RoomScene;

class Entity
{
private:
	//Vector2D pos;
	std::map<componentsEnum, Component*> componentes;
	RoomScene* myScene;
	Component* renderComponent; //el render no tiene update, y solo se le llama para hacer el render, osea q aqui va

public:
//provisional, sentios libres de haced mas metodos, hacerlos virtuales etc
	Entity(/*int, int*/RoomScene* scn);
	void addComponent(componentsEnum, Component*); //posiblemente tengamos q meter un IF para coger el rendercomponent

	virtual ~Entity();
	void update();
	void render();
	Component* getComponent(componentsEnum) const;
	RoomScene* getScene() const;
	Component* getRenderComponent() const;
};

