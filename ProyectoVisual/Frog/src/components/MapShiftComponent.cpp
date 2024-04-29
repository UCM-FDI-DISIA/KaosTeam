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
            static_cast<RenderComponent*>(this->ent->getComponent(RENDER_COMPONENT))->ChangeTexture(textPalanca);
            trigger();
        }
    }
}

void MapShiftComponent::initComponent()
{
    if (ent->getName() == PALANCA_ENTITY) {
        static_cast<ColliderComponent*>(ent->getComponent(COLLIDER_COMPONENT))->GetTransofmCollider()->AddCall([this](Entity* e, Collider c) {collisionPalanca(e, c); }); //Añadimos callback
    }
}
