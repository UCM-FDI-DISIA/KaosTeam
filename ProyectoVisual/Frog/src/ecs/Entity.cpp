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

void Entity::addRenderComponent(RenderComponent* rnd)
{
	renderComponent = rnd;
}

void Entity::addRenderComponentFrog(RenderComponentFrog* rndF)
{
	renderComponentFrog = rndF;
}

void Entity::addRenderComponentSnake(RenderComponentSnake* rndS)
{
	renderComponentSnake = rndS;
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
		if (it->second != nullptr)
			it->second->update();
	}
}

void Entity::render()
{ 
	if (renderComponent != nullptr) { //Si la entidad No es la rana -> Ejecutamos render general
		renderComponent->render();
	}
	else if (renderComponentFrog != nullptr) renderComponentFrog->render(); //Sino, ejecutamos render de la rana (un render mas complejo)
	else if (renderComponentSnake != nullptr) renderComponentSnake->render(); //hay entidades que no se renderizan los objetos de transición
	//else {} //hay entidades que no se renderizan los objetos de transición
}

Component* Entity::getComponent(componentsEnum Identificator) const
{
	if (componentes.count(Identificator) > 0)
		return componentes.at(Identificator);
	else
		return nullptr;
}

RoomScene* Entity::getScene() const
{
	return myScene;
}
