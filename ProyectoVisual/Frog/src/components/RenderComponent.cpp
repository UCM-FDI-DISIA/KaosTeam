#include "RenderComponent.h"
#include "../scenes/RoomScene.h"

void RenderComponent::render()
{
    int t = ent->getScene()->getMapReader()->getTileSize();

    Vector2D pos = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getCasilla();

    SDL_Rect dest;
    dest.x = pos.getX() * t;
    dest.y = pos.getY() * t;
    dest.w = t;
    dest.h = t;

	myTexture->render(dest);
}
