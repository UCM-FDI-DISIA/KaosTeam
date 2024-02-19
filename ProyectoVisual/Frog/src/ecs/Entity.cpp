#include "Entity.h"
#include "Component.h"
void
Entity::update() {
	
	for (auto it = Componentes.begin(); it != Componentes.end(); ++it)
	{
		it->second->update();
	}
}

void Entity::Render()
{
}