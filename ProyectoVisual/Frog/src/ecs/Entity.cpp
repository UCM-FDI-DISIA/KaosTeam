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
	if (id == RENDER_COMPONENT) {
		renderComponent = component;
	}
	componentes.insert(std::pair<componentsEnum, Component*>(id, component));
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
		//it->second->update();
	}
}

void Entity::render()
{ 
	renderComponent->render();
	//RenderComponent* render = componentes.at(componentsEnum::RENDER_COMPONENT); O NO QUIEN SABE
}

Component* Entity::getComponent(componentsEnum Identificator) const
{
	if (componentes.count(Identificator) > 0)
		return componentes.at(Identificator);
	else
		return nullptr;
}

Component* Entity::getRenderComponent() const
{
	return renderComponent;
}

RoomScene* Entity::getScene() const
{
	return myScene;
}
