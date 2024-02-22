#include "Entity.h"
#include "Component.h"
//include rendercomponent()


Entity::Entity(int x, int y): pos(x, y)
{
}

void Entity::addComponent(componentsEnum id, Component* component)
{
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
	//RenderComponent* render = componentes.at(componentsEnum::RENDER_COMPONENT); O NO QUIEN SABE
}

Component* Entity::getComponent(componentsEnum Identificator) const
{
	if (componentes.count(Identificator) > 0)
		return componentes.at(Identificator);
	else
		return nullptr;
}

RenderComponent* Entity::getRenderComponent() const
{
	return renderComponent;
}
