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
	TRANSFORM_COMPONENT,
	COLLIDER_COMPONENT,
	SHADOW_DETECTION
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
	std::map<componentsEnum, Component*> componentes;
	RoomScene* myScene;
	RenderComponent* renderComponent; //el render no tiene update, y solo se le llama para hacer el render, osea q aqui va
	RenderComponentFrog* renderComponentFrog;
	RenderComponentSnake* renderComponentSnake;
	//AnimationComponent* animationComponent;
public:
//provisional, sentios libres de haced mas metodos, hacerlos virtuales etc
	Entity(/*int, int*/RoomScene* scn);
	void addComponent(componentsEnum, Component*); //posiblemente tengamos q meter un IF para coger el rendercomponent
	void addRenderComponent(RenderComponent* rnd);
	void addRenderComponentFrog(RenderComponentFrog* rndF);
	void addRenderComponentSnake(RenderComponentSnake* rndS);
	virtual ~Entity();
	void update();
	void render();
	template<class T>
	T* getComponent(componentsEnum Identificator) const {
		if (componentes.count(Identificator) > 0) {
			return static_cast<T*>(componentes.at(Identificator));
		}
		else
			return nullptr;
	};
	RenderComponentFrog* getRenderComponentFrog() const { return renderComponentFrog; };
	RenderComponentSnake* getRenderComponentSnake() const { return renderComponentSnake; }
	RenderComponent* getRenderComponent() const { return renderComponent; };
	RoomScene* getScene() const;
};

