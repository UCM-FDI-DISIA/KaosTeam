#include "RenderComponentFrog.h"
#include "../scenes/RoomScene.h"
#include "../managers/MapManager.h"
#include "AttackComponentFrog.h"

void RenderComponentFrog::render()
{
    //copiado descaradamente del OG render component
    int t = ent->getScene()->getMapReader()->getTileSize();
    int size = (int)t * scale;
    SDL_Rect dest;
 
    Vector2D offset = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getOffset() + Vector2D((t - size) / 2, (t - size) / 2);
    Vector2D pos = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getPosition();
    Vector2D cameraPos = Camera::instance()->getCameraMovement();

   
    dest.x = (pos.getX() - cameraPos.getX())*t + offset.getX();
    dest.y = (pos.getY() - cameraPos.getY())*t + offset.getY();

    //la lengua 
    if (attacking)
    {
        int distanceMoved = static_cast<AttackComponentFrog*>(ent->getComponent(ATTACK_COMPONENT))->getDistanceMoved();
        if (distanceMoved < 0)
        {
            attacking = false;
        }
        
        else
        {
            //parte del medio
            tongueRect.h = size;
            tongueRect.y = dest.y;
            tongueRect.w = t;
            tongueRect.x = dest.x + size / 2;
            for (int i = 0; i < distanceMoved; i++)
            {
                tongueText->renderFrame(tongueRect, 0, 0);
                tongueRect.x += tongueRect.w;
            }
            
            //punta
            tongueRect.w = tongueRect.h;
            tongueText->renderFrame(tongueRect, 1, 0);

        } 
    }
   
    //renderizamos la rana
    dest.w = size;
    dest.h = size;
    myTexture->renderFrame(dest, 2, 2);
}

void RenderComponentFrog::AttackStart()
{
    attacking = true;
}
