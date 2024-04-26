#include "Entity.h"
#include "Component.h"
#include "../scenes/RoomScene.h"
//include rendercomponent()


Entity::Entity(RoomScene* scn) : name(UNAMED_ENTITY), myScene(scn) {};

Entity::Entity(RoomScene* scn, EntityName name) : name(name), myScene(scn), renderComponent(), renderComponentFrog(),
renderComponentSnake(){};

void Entity::addComponent(ComponentsEnum id, Component* component)
{
	if (componentes.count(id) > 0)
	{
		throw "ya hay un componente";
	}
	componentes.insert(std::pair<ComponentsEnum, Component*>(id, component));
	component->setContext(this);
	component->initComponent();
}

void Entity::addRenderComponent(RenderComponent* rnd)
{
	rnd->setContext(this);
	rnd->initComponent();
	assert(renderComponent == nullptr);
	renderComponent = rnd;
}

void Entity::addRenderComponentFrog(RenderComponentFrog* rndF)
{
	rndF->setContext(this);
	rndF->initComponent();
	assert(renderComponentFrog == nullptr);
	renderComponentFrog = rndF;
}

void Entity::addRenderComponentSnake(RenderComponentSnake* rndS)
{
	rndS->setContext(this);
	rndS->initComponent();
	assert(renderComponentSnake == nullptr);
	renderComponentSnake = rndS;
}

Entity::~Entity()
{
	for (auto it = componentes.begin(); it != componentes.end(); ++it)
	{
		delete it->second;
	}
	delete renderComponent;
	delete renderComponentFrog;
	delete renderComponentSnake;
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

Component* Entity::getComponent(ComponentsEnum Identificator) const
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

EntityName Entity::getName() const
{
	return name;
}