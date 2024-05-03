#include "DestructibleComponent.h"
#include "../sdlutils/RandomNumberGenerator.h"
#include "../scenes/RoomScene.h"
#include <iostream>

DestructibleComponent::DestructibleComponent(int lootType, Vector2D pos) : loot(lootType), rand_(sdlutils().rand()), position(pos)
{}

void DestructibleComponent::DestroySelf()
{
	int auxprob = rand_.nextInt(0, 100);
	switch (loot)
	{
	case LOOT_RANDOM:
		if(auxprob >= RandomLifeProb) {
			if(auxprob <= RandomLifeProb + RandomMoneyProb) SpawnLoot(LOOT_DINERO);
		}
		else SpawnLoot(LOOT_VIDA);
		break;

	case LOOT_VIDA:
		SpawnLoot(LOOT_VIDA);
		break;

	case LOOT_DINERO:
		SpawnLoot(LOOT_DINERO);
		break;

	default:
		break;
	}

	// TODO kms (destroy)
}

void DestructibleComponent::SpawnLoot(int loot)
{
	cout << "DESTRUIBLE (arbusto/jarron) iniciando destruccion" << endl;
}

void DestructibleComponent::CheckCollisions(Entity* ent, Collider c)
{
    if (ent->getName() == FROG_ENTITY) {
        MovementComponentFrog* frogMov = static_cast<MovementComponentFrog*>(ent->getComponent(MOVEMENT_COMPONENT));
        if (c.getName() == TONGUE_COLLIDER) {
			DestructibleComponent::DestroySelf();
        }
        else { //está collisionando con el cuerpo de la rana
            frogMov->cancelMovement();
        }
    }
}

void DestructibleComponent::initComponent()
{
    coll = static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT));

    if (ent->getName() == DESTRUCTIBLE_ENTITY) {
        coll->GetTransofmCollider()->AddCall([this](Entity* e, Collider c) {CheckCollisions(e, c); }); //Añadimos callback
    }
}