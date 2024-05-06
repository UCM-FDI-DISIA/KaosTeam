#pragma once
/*
* Clase base de entidad para una arquitectura de componentes.
*/
#include <map>
//Enum de componentes provisional. Meted los componentes que neceisteis
enum ComponentsEnum
{
	MOVEMENT_COMPONENT,
	LIFE_COMPONENT,
	RENDER_COMPONENT,
	ATTACK_COMPONENT,
	ANIMATION_COMPONENT,
	TRANSITION_COMPONENT,
	INPUT_COMPONENT,
	IACOMPONENT,
	TRANSFORM_COMPONENT,
	COLLIDER_COMPONENT,
	MONEY_COMPONENT,
	TONGUEINTERACT_COMPONENT,
	INVENTORY_COMPONENT,
	EXPLOITABLE_COMPONENT,
	COGIBLE_OBJECT_COMPONENT,
	DESTRUCTIBLE_COMPONENT
};
//Cada entidad puede tener un "nombre". ejs: rana, palanca, pez.
//Si no es relevante, el valor ser� 0 (UNAMED)
enum EntityName {
	UNAMED_ENTITY,
	FROG_ENTITY,
	CRAZY_FROG_ENTITY,
	FISH_ENTITY,
	BLACK_ANT_ENTITY,
	RED_ANT_ENTITY,
	SNAKE_ENTITY,
	BOMB_ENTITY,
	EXPLOITABLE_ENTITY,
	INTERRUPTOR_ENTITY,
	PIEDRAMOV_ENTITY,
	ENGANCHE_ENTITY,
	COGIBLE_ENTITY,
	PALANCA_ENTITY,
	BOTON_ENTITY,
	COCKROACH_ENTITY,
	DESTRUCTIBLE_ENTITY
};

class Component;
class RenderComponent;
class RenderComponentFrog;
class RenderComponentSnake;
class TransformComponent;
class AnimationComponent;
class RoomScene;

class Entity
{
private:
	//Vector2D pos;
	std::map<ComponentsEnum, Component*> componentes;
	RoomScene* myScene;
	RenderComponent* renderComponent; //el render no tiene update, y solo se le llama para hacer el render, osea q aqui va
	RenderComponentFrog* renderComponentFrog;
	RenderComponentSnake* renderComponentSnake;
	EntityName name;
	//AnimationComponent* animationComponent;
public:
	//provisional, sentios libres de haced mas metodos, hacerlos virtuales etc
	Entity(RoomScene* scn);
	Entity(RoomScene* scn, EntityName name);
	void addComponent(ComponentsEnum, Component*); //posiblemente tengamos q meter un IF para coger el rendercomponent
	void addRenderComponent(RenderComponent* rnd);
	void addRenderComponentFrog(RenderComponentFrog* rndF);
	void addRenderComponentSnake(RenderComponentSnake* rndS);
	virtual ~Entity();
	void update();
	void render();
	Component* getComponent(ComponentsEnum) const;
	RenderComponentFrog* getRenderComponentFrog() const { return renderComponentFrog; };
	RenderComponentSnake* getRenderComponentSnake() const { return renderComponentSnake; }
	RenderComponent* getRenderComponent() const { return renderComponent; };
	RoomScene* getScene() const;
	EntityName getName() const;
};