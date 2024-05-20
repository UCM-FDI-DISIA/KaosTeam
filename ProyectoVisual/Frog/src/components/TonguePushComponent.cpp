#include "TonguePushComponent.h"
#include <iostream>

void TonguePushComponent::checkCollisionsTongue(Entity* ent, Collider c)
{
    if (ent->getName() == FROG_ENTITY) {
        MovementComponentFrog* frogMov = static_cast<MovementComponentFrog*>(ent->getComponent(MOVEMENT_COMPONENT));
            Directions d = frogMov->getDirection();
            TransformComponent* t = static_cast<TransformComponent*>(this->ent->getComponent(TRANSFORM_COMPONENT));
        if (c.getName() == TONGUE_COLLIDER) {
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
            DataManager::GetInstance()->getInteractObj(this->ent->getScene()->getPath())[objIntID].interacted = true;
            DataManager::GetInstance()->getInteractObj(this->ent->getScene()->getPath())[objIntID].pos = t->getCasilla();
            sdlutils().soundEffects().at("Roca").play();
        }
        else { //está collisionando con el cuerpo de la rana
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

void TonguePushComponent::initComponent()
{
	coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));

	if (ent->getName() == PIEDRAMOV_ENTITY) {
		coll->GetTransofmCollider()->AddCall([this](Entity* e, Collider c) {checkCollisionsTongue(e, c); }); //Añadimos callback
	}
}
