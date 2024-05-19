#include "ConveyorBeltComponent.h"
#include "../scenes/RoomScene.h"
#include <iostream>

ConveyorBeltComponent::ConveyorBeltComponent(int direccion, Vector2D pos) : direction(direccion), position(pos)
{}

void CheckCollisionsBelt(Entity* ent, Collider c)
{
    TransformComponent* ObjTrans = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));

    if(ent->getName() == CONVEYOR_ENTITY)
    {



    }
}

void ConveyorBeltComponent::initComponent()
{
    coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));

    if (ent->getName() == CONVEYOR_ENTITY) {
        coll->GetTransofmCollider()->AddCall([this](Entity* e, Collider c) {CheckCollisionsBelt(e, c); }); //Añadimos callback
    }

    scen = static_cast<RoomScene*>(ent->getScene());
}