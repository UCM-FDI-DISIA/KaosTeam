#include "RenderComponent.h"
#include "../scenes/RoomScene.h"
#include "MovementComponent.h"

void RenderComponent::render()
{
    int t = ent->getScene()->getMapReader()->getTileSize();
    int size = (int)t * scale;
    SDL_Rect dest;

    Vector2D offset = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getOffset() //el offset el objeto
        + Vector2D((t - size) / 2, (t - size) / 2);                                             //para que este centrado en la casilla
    Vector2D pos = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getPosition();
    Vector2D cameraPos = Camera::instance()->getCameraMovement();


    dest.x = pos.getX() * t + offset.getX() - cameraPos.getX();
    dest.y = pos.getY() * t + offset.getY() - cameraPos.getY();

    dest.w = size;
    dest.h = size;

	myTexture->renderFrame(dest, myAnimator->getCurrentFil(), myAnimator->getCurrentCol());
}
