#include "TonguePushComponent.h"
#include <iostream>

void TonguePushComponent::checkCollisionsTongue(Entity* ent, Collider c)
{
	switch (c.getName()) {
	case ColliderName::TONGUE_COLLIDER:
        Directions d = static_cast<MovementComponentFrog*>(ent->getComponent(MOVEMENT_COMPONENT))->getDirection();
        TransformComponent* t = static_cast<TransformComponent*>(this->ent->getComponent(TRANSFORM_COMPONENT));
        switch (d) { //Se configura como se empieza a renderizar la lengua
        case Directions::LEFT:
            t->changePos({ t->getCasilla().getX() - 1, t->getCasilla().getY() });
            break;
        case Directions::RIGHT:
            t->changePos({ t->getCasilla().getX() + 1, t->getCasilla().getY() });
            break;
        case Directions::UP:
            t->changePos({ t->getCasilla().getX(), t->getCasilla().getY() - 1});
            break;
        case Directions::DOWN:
            t->changePos({ t->getCasilla().getX(), t->getCasilla().getY() + 1});            
            break;
        default:
            break;
        }
		break;
	//...Mas casos
	}
}

void TonguePushComponent::initComponent()
{
	coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));

	if (ent->getName() == PIEDRAMOV_ENTITY) {
		//Añadimos funcion de collider a la bomba
		//std::list<Collider> listCol = coll->GetColliders(); //Accedemos a la lista de colliders
		coll->GetTransofmCollider()->AddCall([this](Entity* e, Collider c) {checkCollisionsTongue(e, c); }); //Añadimos callback
	}
}
