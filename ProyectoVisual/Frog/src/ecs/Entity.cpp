#include "Entity.h"
#include "Component.h"
#include "../scenes/RoomScene.h"
//include rendercomponent()


Entity::Entity(/*int x, int y*/RoomScene* scn) /*: pos(x, y)*/
{
	if (scn == nullptr) {
		std::cout << "scn null";
	}
	myScene = scn;
}

void Entity::addComponent(componentsEnum id, Component* component)
{
	componentes.insert(std::pair<componentsEnum, Component*>(id, component));
}

void Entity::addAnimationComponent(AnimationComponent* animComponent) {
	this->animationComponent = animComponent;
}

Entity::~Entity()
{
	for (auto it = componentes.begin(); it != componentes.end(); ++it)
	{
		delete it->second;
	}
}

void
Entity::update() {
	
	for (auto it = componentes.begin(); it != componentes.end(); ++it)
	{
		it->second->update();
	}
}

void Entity::render()
{ 
	animationComponent->update();
	animationComponent->render();
	//RenderComponent* render = componentes.at(componentsEnum::RENDER_COMPONENT); O NO QUIEN SABE
}

Component* Entity::getComponent(componentsEnum Identificator) const
{
	if (componentes.count(Identificator) > 0)
		return componentes.at(Identificator);
	else
		return nullptr;
}

Component* Entity::getAnimationComponent() const
{
	return animationComponent;
}

RoomScene* Entity::getScene() const
{
	return myScene;
}
