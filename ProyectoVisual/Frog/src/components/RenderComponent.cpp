#include "RenderComponent.h"
#include "../scenes/RoomScene.h"

void RenderComponent::render()
{
    int t = ent->getScene()->getMapReader()->getTileSize();
    int size = (int) t*scale;

    Vector2D pos = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getCasilla();

    SDL_Rect dest;
    dest.w = size;
    dest.h = size;

    dest.x = pos.getX() * t + ((t-size)/2);
    dest.y = pos.getY() * t + ((t - size)/2);

	myTexture->render(dest);
}
