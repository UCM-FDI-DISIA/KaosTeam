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
	ATTACK_COMPONENT,
	ANIMATION_COMPONENT,
	TRANSITION_COMPONENT,
	INPUT_COMPONENT,
	IACOMPONENT,
	TRANSFORM_COMPONENT
};
class Component;
class RenderComponent;
class RenderComponentFrog;
class AnimationComponent;
class RoomScene;
class Entity
{
private:
	//Vector2D pos;
	std::map<componentsEnum, Component*> componentes;
	RoomScene* myScene;
	RenderComponent* renderComponent; //el render no tiene update, y solo se le llama para hacer el render, osea q aqui va
	RenderComponentFrog* renderComponentFrog;
	//AnimationComponent* animationComponent;
public:
//provisional, sentios libres de haced mas metodos, hacerlos virtuales etc
	Entity(/*int, int*/RoomScene* scn);
	void addComponent(componentsEnum, Component*); //posiblemente tengamos q meter un IF para coger el rendercomponent
	void addRenderComponent(RenderComponent* rnd);
	void addRenderComponentFrog(RenderComponentFrog* rndF);
	virtual ~Entity();
	void update();
	void render();
	Component* getComponent(componentsEnum) const;
	RenderComponentFrog* getRenderComponentFrog() const { return renderComponentFrog; };
	RoomScene* getScene() const;
};

