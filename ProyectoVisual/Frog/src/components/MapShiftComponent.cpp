#include "MapShiftComponent.h"
#include <iostream>

void MapShiftComponent::trigger()
{
    if (!shifted) {
        this->ent->getScene()->getMapReader()->loadBg(_nextMap, sdlutils().renderer());
        shifted = true;
    }
}

void MapShiftComponent::collisionPalanca(Entity* ent, Collider c)
{
    if (ent->getName() == FROG_ENTITY) {
        if (c.getName() == TONGUE_COLLIDER) {
            Texture* textPalanca = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/PalancaB.png", 1, 1);
            static_cast<RenderComponent*>(this->ent->getRenderComponent())->ChangeTexture(textPalanca);
            sdlutils().soundEffects().at("Palanca").play();
            trigger();
        }
    }
}

void MapShiftComponent::collisionBoton(Entity* ent, Collider c)
{
    if (ent->getName() == FROG_ENTITY) {
        if (c.getName() == TRANSFORM_COLLIDER) {
            Texture* textBoton = new Texture(sdlutils().renderer(), "../Frog/resources/sprites/BotonB.png", 1, 1);
            static_cast<RenderComponent*>(this->ent->getRenderComponent())->ChangeTexture(textBoton);
            sdlutils().soundEffects().at("Palanca").play(); //reutilizamos el sonido de la palanca
            trigger();
        }
    }
}

void MapShiftComponent::initComponent()
{
    if (ent->getName() == PALANCA_ENTITY) {
        static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->GetTransformCollider()->AddCall([this](Entity* e, Collider c) {collisionPalanca(e, c); }); //Añadimos callback
    }
    else if (ent->getName() == BOTON_ENTITY) {
        static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->GetTransformCollider()->AddCall([this](Entity* e, Collider c) {collisionBoton(e, c); }); //Añadimos callback
    }
}
