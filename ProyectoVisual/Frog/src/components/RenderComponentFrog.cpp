#include "RenderComponentFrog.h"
#include "../scenes/RoomScene.h"
#include "../managers/MapManager.h"
#include "AttackComponentFrog.h"
#include "AnimationComponent.h"

void RenderComponentFrog::render()
{
    int t = ent->getScene()->getMapReader()->getTileSize();
    int size = (int)t * sc;
    SDL_Rect dest;
 
    Vector2D offset = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getOffset() + Vector2D((t - size) / 2, (t - size) / 2);
    Vector2D pos = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getPosition();
    Vector2D cameraPos = Camera::instance()->getCameraMovement();

   
    dest.x = (pos.getX() - cameraPos.getX())*t + offset.getX();
    dest.y = (pos.getY() - cameraPos.getY())*t + offset.getY();

    //la lengua 
    if (attacking) {
        int distanceMoved = static_cast<AttackComponentFrog*>(ent->getComponent(ATTACK_COMPONENT))->getDistanceMoved();
        if (distanceMoved < 0)
            attacking = false;
        else {
            Directions d = static_cast<MovementComponentFrog*>(ent->getComponent(MOVEMENT_COMPONENT))->getDirection(); //Obtenemos direccion actual
            float endAngle = 0.0f;
            SDL_RendererFlip endFlip = SDL_FLIP_NONE;

            //parte del medio
            tongueRect.h = size;
            tongueRect.w = t;
            tongueRect.y = dest.y;
            tongueRect.x = dest.x + (size / 2);


            for (int i = 0; i < distanceMoved; i++) {
                switch (d) { //Dependdiendo de la direccion, se renderiza en una dir u otra
                case Directions::LEFT:
                    playAnimation("ATTACK_LEFT");
                    endFlip = SDL_FLIP_HORIZONTAL;
                    tongueText->renderFrameWithFlip(tongueRect, 0, 0, endFlip, endAngle);
                    tongueRect.x -= tongueRect.w;
                    break;
                case Directions::RIGHT:
                    playAnimation("ATTACK_RIGHT");
                    tongueText->renderFrameWithFlip(tongueRect, 0, 0, endFlip, endAngle);
                    tongueRect.x += tongueRect.w;
                    break;
                case Directions::UP:
                    playAnimation("ATTACK_UP");
                    endAngle = -90.0f;
                    tongueText->renderFrameWithFlip(tongueRect, 0, 0, endFlip, endAngle);
                    tongueRect.y -= tongueRect.h;
                    break;
                case Directions::DOWN:
                    playAnimation("ATTACK_DOWN");
                    endAngle = 90.0f;
                    tongueText->renderFrameWithFlip(tongueRect, 0, 0, endFlip, endAngle);
                    tongueRect.y += tongueRect.h;
                    break;
                default:
                    break;
                }
            }
            //punta
            tongueRect.w = tongueRect.h;
            tongueText->renderFrameWithFlip(tongueRect, 1, 0, endFlip, endAngle);
        }
    }
    //renderizamos la rana
    dest.w = size;
    dest.h = size;

    if (getCurrentAnim().flip) //Si se tiene que flipear
        tex_->renderFrameWithFlip(dest, currentFrameR_, currentFrameC_, SDL_FLIP_HORIZONTAL, 0);
    else
        tex_->renderFrame(dest, currentFrameR_, currentFrameC_);
}

void RenderComponentFrog::AttackStart() {
    attacking = true;
}
