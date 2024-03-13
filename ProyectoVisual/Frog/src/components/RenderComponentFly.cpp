#include "RenderComponentFly.h"
#include "../scenes/RoomScene.h"

void RenderComponentFly::render() {

    int t = ent->getScene()->getMapReader()->getTileSize();
    int size = (int)t * sc;

    Vector2D pos = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getPosition();
    Vector2D offset = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getOffset() + Vector2D((t - size) / 2, (t - size) / 2);

    SDL_Rect dest;
    //COSAS IMPORTANTES. pos es de floats, igual nos conviene q sea de ints
    //TAMBIÉN, el dest podriamos definirlo en la costructora para ahorrar tiempo y cambiar solo su x e y
    //Y TAMBIÉN. ESTO NO SIRVE SI SE MUEVE LA CAMARA.
    dest.x = pos.getX() * t + offset.getX();
    dest.y = pos.getY() * t + offset.getY();
    dest.w = size;
    dest.h = size;

    tex_->renderFrame(dest, currentFrameR_, currentFrameC_);
}

