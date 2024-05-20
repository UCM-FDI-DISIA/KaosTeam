#include "PuertaComponent.h"
#include <iostream>

void PuertaComponent::checkCollisionsTongue(Entity* ent, Collider c)
{
    if (ent->getName() == FROG_ENTITY) {
        int i = static_cast<InventoryComponent*>(ent->getComponent(INVENTORY_COMPONENT))->GetLlaves();
        if (i == 0) { //está collisionando con el cuerpo de la rana
            MovementComponentFrog* frogMov = static_cast<MovementComponentFrog*>(ent->getComponent(MOVEMENT_COMPONENT));
            Directions d = frogMov->getDirection();
            TransformComponent* t = static_cast<TransformComponent*>(this->ent->getComponent(TRANSFORM_COMPONENT));
            TransformComponent* tFrog = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
            switch (d) { //Se configura como se empieza a renderizar la lengua
            case Directions::LEFT:
                if (tFrog->getCasilla().getX() > t->getCasilla().getX() && tFrog->getCasilla().getY() == t->getCasilla().getY()) {
                    frogMov->cancelMovement();
                }
                break;
            case Directions::RIGHT:
                if (tFrog->getCasilla().getX() < t->getCasilla().getX() && tFrog->getCasilla().getY() == t->getCasilla().getY()) {
                    frogMov->cancelMovement();
                }
                break;
            case Directions::UP:
                if (tFrog->getCasilla().getY() > t->getCasilla().getY() && tFrog->getCasilla().getX() == t->getCasilla().getX()) {
                    frogMov->cancelMovement();
                }
                break;
            case Directions::DOWN:
                if (tFrog->getCasilla().getY() < t->getCasilla().getY() && tFrog->getCasilla().getX() == t->getCasilla().getX()) {
                    frogMov->cancelMovement();
                }
                break;
            default:
                break;
            }
        }
    }
}

void PuertaComponent::initComponent()
{
    coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));

    if (ent->getName() == PUERTA_ENTITY) {
        coll->GetTransformCollider()->AddCall([this](Entity* e, Collider c) {checkCollisionsTongue(e, c); }); //Añadimos callback
    }
}
