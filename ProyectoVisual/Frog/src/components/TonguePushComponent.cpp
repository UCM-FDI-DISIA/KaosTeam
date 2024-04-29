#include "TonguePushComponent.h"
#include <iostream>

void TonguePushComponent::checkCollisionsTongue(Entity* ent, Collider c)
{
    if (ent->getName() == FROG_ENTITY) {
        MovementComponentFrog* frogMov = static_cast<MovementComponentFrog*>(ent->getComponent(MOVEMENT_COMPONENT));
        if (c.getName() == TONGUE_COLLIDER) {
            Directions d = frogMov->getDirection();
            TransformComponent* t = static_cast<TransformComponent*>(this->ent->getComponent(TRANSFORM_COMPONENT));
            switch (d) { //Se configura como se empieza a renderizar la lengua
            case Directions::LEFT:
                t->changePos({ t->getCasilla().getX() - 1, t->getCasilla().getY() });
                break;
            case Directions::RIGHT:
                t->changePos({ t->getCasilla().getX() + 1, t->getCasilla().getY() });
                break;
            case Directions::UP:
                t->changePos({ t->getCasilla().getX(), t->getCasilla().getY() - 1 });
                break;
            case Directions::DOWN:
                t->changePos({ t->getCasilla().getX(), t->getCasilla().getY() + 1 });
                break;
            default:
                break;
            }
        }
        else { //está collisionando con el cuerpo de la rana
            frogMov->cancelMovement();
        }
	}
}

void TonguePushComponent::initComponent()
{
	coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));

	if (ent->getName() == PIEDRAMOV_ENTITY) {
		coll->GetTransofmCollider()->AddCall([this](Entity* e, Collider c) {checkCollisionsTongue(e, c); }); //Añadimos callback
	}
}
