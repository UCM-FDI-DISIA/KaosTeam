#include "TongueInteract.h"
#include <iostream>

void TongueInteract::checkCollisionsTongue(Entity* ent, Collider c)
{
	/*
	switch (c->getName()) {
	case EntityName::FROG_ENTITY:
		//Destruimos la puerta: ent-> MetodoAlQueLlamar(); 
		std::cout << "M ha tocado la rana" << std::endl;
		break;
	//...Mas casos
	}
	std::cout << ent->getName() << std::endl;
	*/
}

void TongueInteract::initComponent()
{
	coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));

	if (ent->getName() == PIEDRAMOV_ENTITY) {
		//Añadimos funcion de collider a la bomba
		//std::list<Collider> listCol = coll->GetColliders(); //Accedemos a la lista de colliders
		coll->GetTransofmCollider()->AddCall([this](Entity* e, Collider c) {checkCollisionsTongue(e, c); }); //Añadimos callback
	}
}
