#include "RenderComponent.h"
#include "../scenes/RoomScene.h"
#include "MovementComponent.h"

void RenderComponent::render()
{
    int t = ent->getScene()->getMapReader()->getTileSize();
    int size = (int)t * scale;
    SDL_Rect dest;

    Vector2D offset = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getOffset() + Vector2D((t - size) / 2, (t - size) / 2);
    Vector2D pos = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getPosition();
    Vector2D cameraPos = Camera::instance()->getCameraMovement();
    
      
    dest.x = (pos.getX() - cameraPos.getX()) * t + offset.getX();
    dest.y = (pos.getY() - cameraPos.getY()) * t + offset.getY();

    dest.w = size;
    dest.h = size;
   

    //PROVISIONAL CON MOV CAMARA
    /*
    if (ent->getComponent(ATTACK_COMPONENT) != nullptr) {
        int x = ent->getScene()->getMapReader()->getMapSize().getX();
        int i = pos.getX() + (pos.getY() * x - 1);
        std::cout << "Buscando en: " << i << std::endl;
        ent->getScene()->getMapReader()->getTile(i)->x;
        dest.x = (-300 + ent->getScene()->getMapReader()->getTile(i)->x)*6;
        dest.y = (-200 + ent->getScene()->getMapReader()->getTile(i)->y)*6;
    }
    else {
        dest.x = pos.getX() * t + offset;
        dest.y = pos.getY() * t + offset;
    }
    */

    if (myAnimator->getCurrentAnim().flip) //Si se tiene que flipear
        myTexture->renderFrameWithFlip(dest, myAnimator->getCurrentFil(), myAnimator->getCurrentCol(), SDL_FLIP_HORIZONTAL, 0);
    else
        myTexture->renderFrame(dest, myAnimator->getCurrentFil(), myAnimator->getCurrentCol());
}
