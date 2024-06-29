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
	BOSS_COMPONENT,
	MONEY_COMPONENT,
	TONGUEINTERACT_COMPONENT,
	INVENTORY_COMPONENT,
	EXPLOITABLE_COMPONENT,
	COGIBLE_OBJECT_COMPONENT,
	DESTRUCTIBLE_COMPONENT,
	CONVEYOR_COMPONENT,
	SWALLOW_COMPONENT,
	ITEM_THROWER_COMPONENT,
	DAMAGE_COMPONENT,
	TERMITE_GENERATOR_COMPONENT,
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
	FRENCH_ENTITY,
	CUTLERY_ENTITY,
	PALANCA_ENTITY,
	BOTON_ENTITY,
	COCKROACH_ENTITY,
	DESTRUCTIBLE_ENTITY,
	TERMITELOG_ENTITY,
	TERMITE_ENTITY,
	PUERTA_ENTITY,
	CONVEYOR_ENTITY,
	MULTISQUARE_ENTITY
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
	//Referencia la escena en la que se encuentra la entidad.
	RoomScene* myScene;
	RenderComponent* renderComponent; //el render no tiene update, y solo se le llama para hacer el render, osea q aqui va
	//Estos dos son un poco raritos. La entidad puede tener o no tener alguno de estos.
	RenderComponentFrog* renderComponentFrog;
	RenderComponentSnake* renderComponentSnake;

	EntityName name; //El tipo de esta entidad
	//AnimationComponent* animationComponent;
public:
	//provisional, sentios libres de haced mas metodos, hacerlos virtuales etc
	Entity(RoomScene* scn);
	Entity(RoomScene* scn, EntityName name);
	//Añade un componente al mapa de componentes por su tipo
	void addComponent(ComponentsEnum, Component*);
	void addRenderComponent(RenderComponent* rnd);
	void addRenderComponentFrog(RenderComponentFrog* rndF);
	void addRenderComponentSnake(RenderComponentSnake* rndS);
	virtual ~Entity();
	//A ser llamado una vez por frame. Llama a todos los componentes del mapa de componentes a sus respectivos update.
	void update();
	//A ser llamado una vez por frame, siempre después del Update. Llama al componente de renderizado para lo que tenga que hacer.
	void render();
	//Busca el componente en el mapa de componentes a partir del tipo.
	Component* getComponent(ComponentsEnum) const;
	RenderComponentFrog* getRenderComponentFrog() const { return renderComponentFrog; };
	RenderComponentSnake* getRenderComponentSnake() const { return renderComponentSnake; }
	RenderComponent* getRenderComponent() const { return renderComponent; };
	RoomScene* getScene() const;
	EntityName getName() const;
};