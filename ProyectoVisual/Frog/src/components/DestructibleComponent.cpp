#include "DestructibleComponent.h"
#include "../scenes/RoomScene.h"
#include <iostream>

DestructibleComponent::DestructibleComponent(int lootType, Vector2D pos) : loot(lootType), rand_(sdlutils().rand()), position(pos)
{}

void DestructibleComponent::LootAndBreak()
{
	int auxprob = rand_.nextInt(0, 100);

	// generadores comentados hasta que se tenga dinero y vida
    if (!broken) {
        broken = true;

        switch (loot)   // spawnea el loot
        {
        case LOOT_RANDOM:
            if (auxprob >= RandomLifeProb) {
                if (auxprob <= RandomLifeProb + RandomMoneyProb)
                {
                    scen->createMoneda(position, MONEDA_ROSA);
                    cout << "Rompible generando dinero" << endl;
                }
            }
            else
            {
                scen->createLifeFly(position);
                cout << "Rompible generando vida" << endl;
            }
            break;

        case LOOT_VIDA:
            scen->createLifeFly(position);
            cout << "Rompible generando vida " << endl;
            break;

        case LOOT_DINERO:
            scen->createMoneda(position, MONEDA_ROSA);
            cout << "Rompible generando dinero" << endl;
            break;

        default:
            break;
        }
        cout << "DESTRUIBLE (arbusto/jarron) iniciando destruccion" << endl;
    }

	scen->removeEntity(this->ent);
}

void DestructibleComponent::CheckCollisions(Entity* ent, Collider c)
{
    if (ent->getName() == FROG_ENTITY) {
        MovementComponentFrog* frogMov = static_cast<MovementComponentFrog*>(ent->getComponent(MOVEMENT_COMPONENT));
        Directions d = frogMov->getDirection();
        TransformComponent* t = static_cast<TransformComponent*>(this->ent->getComponent(TRANSFORM_COMPONENT));

        if (c.getName() == TONGUE_COLLIDER) // est� colisionando con la lengua
        {   
			DestructibleComponent::LootAndBreak();
            sdlutils().soundEffects().at("Jarra").play();
        }
        else { //est� collisionando con el cuerpo de la rana
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

void DestructibleComponent::initComponent() // inicializador
{
    coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));

    if (ent->getName() == DESTRUCTIBLE_ENTITY) {
        coll->GetTransformCollider()->AddCall([this](Entity* e, Collider c) {CheckCollisions(e, c); }); //A�adimos callback
    }

	scen = static_cast<RoomScene*>(ent->getScene());
}