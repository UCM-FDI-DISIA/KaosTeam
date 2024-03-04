#include "RenderComponentFrog.h"
#include "../scenes/RoomScene.h"
#include "AttackComponent.h"

void RenderComponentFrog::render()
{
    //copiado descaradamente del OG render component
    int t = ent->getScene()->getMapReader()->getTileSize();
    int size = (int)t * scale;
    int offset = (t - size) / 2;
    Vector2D pos = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getPosition();
    //Vector2D pos = Vector2D(2, 2);
    
    SDL_Rect dest;
    //COSAS IMPORTANTES. pos es de floats, igual nos conviene q sea de ints
    //TAMBIÉN, el dest podriamos definirlo en la costructora para ahorrar tiempo y cambiar solo su x e y
    //Y TAMBIÉN. ESTO NO SIRVE SI SE MUEVE LA CAMARA.
    dest.x = pos.getX() * t + offset;
    dest.y = pos.getY() * t + offset;

    //la lengua 
    int distanceMoved = static_cast<AttackComponent*>(ent->getComponent(ATTACK_COMPONENT))->getDistanceMoved();
    if (distanceMoved > 0)
    {
        //parte del medio
        tongueRect.h = size;
        tongueRect.y = dest.y;
        tongueRect.w = (distanceMoved)*t;
        tongueRect.x = dest.x + size / 2;
        tongueText->renderFrame(tongueRect, 0, 0);

        //punta
        tongueRect.x += tongueRect.w;
        tongueRect.w = tongueRect.h;
        tongueText->renderFrame(tongueRect, 1, 0);
    }



    //renderizamos la rana
    dest.w = size;
    dest.h = size;

    

    myTexture->renderFrame(dest, 2, 2);

    
}
