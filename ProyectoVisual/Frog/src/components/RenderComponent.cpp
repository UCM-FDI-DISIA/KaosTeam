#include "RenderComponent.h"
#include "../scenes/RoomScene.h"

void RenderComponent::render()
{
    int t = ent->getScene()->getMapReader()->getTileSize();
    int size = (int) t*scale;
    int offset = (t - size) / 2;

    Vector2D pos = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getCasilla();

    SDL_Rect dest;
    dest.w = size;
    dest.h = size;

    //COSAS IMPORTANTES. pos es de floats, igual nos conviene q sea de ints
    //TAMBIÉN, el dest podriamos definirlo en la costructora para ahorrar tiempo y cambiar solo su x e y
    //Y TAMBIÉN. ESTO NO SIRVE SI SE MUEVE LA CAMARA.
    dest.x = pos.getX() * t + offset; 
    dest.y = pos.getY() * t + offset;

	myTexture->renderFrame(dest, 0, 0);
}
