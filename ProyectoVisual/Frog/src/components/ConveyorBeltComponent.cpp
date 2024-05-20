#include "ConveyorBeltComponent.h"
#include "../scenes/RoomScene.h"
#include <iostream>


ConveyorBeltComponent::ConveyorBeltComponent(int direccion, Vector2D pos) : direction(direccion), position(pos)
{}

void ConveyorBeltComponent::CheckCollisionsBelt(Entity* ent, Collider c)
{
    TransformComponent* ObjTrans = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));

    cout << "Detecta colison";

    if(true && DataManager::GetInstance()->getFrameTime() - lastTimeMoved > COOLDOWN)
    {
        lastTimeMoved = DataManager::GetInstance()->getFrameTime();
        switch (direction)
        {
        case NORTE:
            ObjTrans->changePos(position + Vector2D(0, -1));
            break;
        case ESTE:
            ObjTrans->changePos(position + Vector2D(1, 0));
            break;
        case SUR:
            ObjTrans->changePos(position + Vector2D(0, 1));
            break;
        case OESTE:
            ObjTrans->changePos(position + Vector2D(-1, 0));
            break;
        default:
            break;
        }
        
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