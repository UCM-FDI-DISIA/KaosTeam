#include "MultiBlockComponent.h"
#include "../scenes/RoomScene.h"
#include <iostream>


MultiBlockComponent::MultiBlockComponent(Vector2D(pos)) : position(pos) 
{}

void MultiBlockComponent::CheckCollisions(Entity* ent, Collider c)  // revisa si ha habido choque de la rana e impide que pase
{
    if (ent->getName() == FROG_ENTITY) {
        MovementComponentFrog* frogMov = static_cast<MovementComponentFrog*>(ent->getComponent(MOVEMENT_COMPONENT));
        Directions d = frogMov->getDirection();
        TransformComponent* t = static_cast<TransformComponent*>(this->ent->getComponent(TRANSFORM_COMPONENT));
            TransformComponent* tFrog = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
            switch (d) { 
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

void MultiBlockComponent::initComponent() // inicializador
{
    coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));

    if (ent->getName() == MULTISQUARE_ENTITY) {
        coll->GetTransformCollider()->AddCall([this](Entity* e, Collider c) {CheckCollisions(e, c); }); //Añadimos callback
    }

    scen = static_cast<RoomScene*>(ent->getScene());
}
