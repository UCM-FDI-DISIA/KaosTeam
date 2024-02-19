#include "Entity.h"
#include "Component.h"
void
Entity::update() {
	
	for (auto it = componentes.begin(); it != componentes.end(); ++it)
	{
		it->second->update();
	}
}

void Entity::Render()
{
}

Component* Entity::getComponent(componentsEnum Identificator) const
{
	return componentes.at(Identificator);
}