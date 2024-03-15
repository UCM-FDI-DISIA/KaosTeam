#include "RenderComponentFrog.h"
#include "../scenes/RoomScene.h"
#include "../managers/MapManager.h"
#include "AttackComponentFrog.h"

void RenderComponentFrog::render()
{
    //copiado descaradamente del OG render component
    int t = ent->getScene()->getMapReader()->getTileSize();
    int size = (int)t * scale;
  
    tile* actualTile = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getTile();
    Vector2D offset = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getOffset() + Vector2D((t - size) / 2, (t - size) / 2);
    
    
    SDL_Rect dest;

    //COSAS IMPORTANTES. pos es de floats, igual nos conviene q sea de ints
    //TAMBI�N, el dest podriamos definirlo en la costructora para ahorrar tiempo y cambiar solo su x e y
    //Y TAMBI�N. ESTO NO SIRVE SI SE MUEVE LA CAMARA.
    dest.x = actualTile->x + offset.getX();
    dest.y = actualTile->y + offset.getY();

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
