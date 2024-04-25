#include "TongueHookComponent.h"
#include <iostream>

void TongueHookComponent::checkCollisionsTongue(Entity* _ent, Collider c)
{
    if (_ent->getName() == FROG_ENTITY) {
        MovementComponentFrog* frogMov = static_cast<MovementComponentFrog*>(_ent->getComponent(MOVEMENT_COMPONENT));
        if (c.getName() == TONGUE_COLLIDER) {
            if (static_cast<AttackComponentFrog*>(_ent->getComponent(ATTACK_COMPONENT))->attackHasHook() &&
                (static_cast<TransformComponent*>(_ent->getComponent(TRANSFORM_COMPONENT))->getCasilla() !=
                    static_cast<TransformComponent*>(this->ent->getComponent(TRANSFORM_COMPONENT))->getCasilla())) {
                Vector2D newPos = static_cast<TransformComponent*>(this->ent->getComponent(TRANSFORM_COMPONENT))->getCasilla();
                frogMov->hookAttract(newPos);
            }
        }
    }
}

void TongueHookComponent::initComponent()
{
    coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));

    if (ent->getName() == ENGANCHE_ENTITY) {
        coll->GetTransofmCollider()->AddCall([this](Entity* e, Collider c) {checkCollisionsTongue(e, c); }); //Añadimos callback
    }
}
