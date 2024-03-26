#include "RenderComponentFrog.h"
#include "../scenes/RoomScene.h"
#include "../managers/MapManager.h"
#include "AttackComponentFrog.h"
#include "AnimationComponent.h"

void RenderComponentFrog::render()
{
    int t = ent->getScene()->getMapReader()->getTileSize();
    int size = (int)t * scale;
    SDL_Rect frogRect; // Rect de la rana
    SDL_Rect tongueRect;
 
    Vector2D offset = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getOffset() //el offset el objeto
                    + Vector2D((t - size) / 2, (t - size) / 2);                                             //para que este centrado en la casilla
    Vector2D pos = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT))->getPosition();
    Vector2D cameraPos = Camera::instance()->getCameraMovement();

   
    frogRect.x = pos.getX() * t + offset.getX() - cameraPos.getX();
    frogRect.y = pos.getY() * t + offset.getY() -cameraPos.getY();

    //la lengua 
    if (attacking) {
        int distanceMoved = static_cast<AttackComponentFrog*>(ent->getComponent(ATTACK_COMPONENT))->getDistanceMoved();
        Directions d = static_cast<MovementComponentFrog*>(ent->getComponent(MOVEMENT_COMPONENT))->getDirection(); //Obtenemos direccion actual

        if (distanceMoved < 0) { //Si el ataque acaba
            attacking = false;
            switch (d) { //Se reproduce el idle correspondiente
            case Directions::LEFT:
                frogAnimator->playAnimation("IDLE_LEFT");
                break;
            case Directions::RIGHT:
                frogAnimator->playAnimation("IDLE_RIGHT");
                break;
            case Directions::UP:
                frogAnimator->playAnimation("IDLE_UP");
                break;
            case Directions::DOWN:
                frogAnimator->playAnimation("IDLE_DOWN");
                break;
            default:
                break;
            }
        }
        else { //Sino, se renderiza el ataque
            //parte del medio
            tongueRect.h = size;
            tongueRect.w = t;
            tongueRect.y = frogRect.y;
            tongueRect.x = frogRect.x + size / 2;

            float endAngle = 0.0f;
            SDL_RendererFlip endFlip = SDL_FLIP_NONE;

            switch (d) { //Se configura como se empieza a renderizar la lengua
            case Directions::LEFT:
                tongueRect.x = frogRect.x - size / 2; 
                endFlip = SDL_FLIP_HORIZONTAL;
                break;
            case Directions::RIGHT:
                tongueRect.x = frogRect.x + size / 2;
                break;
            case Directions::UP:
                tongueRect.y = frogRect.y - size / 2;
                tongueRect.x = frogRect.x + 5;
                endAngle = -90.0f;
                break;
            case Directions::DOWN:
                tongueRect.y = frogRect.y + size / 2; 
                tongueRect.x = frogRect.x - 5;
                endAngle = 90.0f;
                break;
            default:
                break;
            }
            for (int i = 0; i < distanceMoved; i++) {
                switch (d) { //Dependiendo de la direccion, la lengua se alarga en una dir u otra
                case Directions::LEFT:
                    frogAnimator->playAnimation("ATTACK_LEFT");
                    tongueText->renderFrameWithFlip(tongueRect, 0, 0, endFlip, endAngle);
                    tongueRect.x -= tongueRect.w;
                    break;
                case Directions::RIGHT:
                    frogAnimator->playAnimation("ATTACK_RIGHT");
                    tongueText->renderFrameWithFlip(tongueRect, 0, 0, endFlip, endAngle);
                    tongueRect.x += tongueRect.w;
                    break;
                case Directions::UP:
                    frogAnimator->playAnimation("ATTACK_UP");
                    tongueText->renderFrameWithFlip(tongueRect, 0, 0, endFlip, endAngle);
                    tongueRect.y -= tongueRect.h;
                    break;
                case Directions::DOWN:
                    frogAnimator->playAnimation("ATTACK_DOWN");
                    tongueText->renderFrameWithFlip(tongueRect, 0, 0, endFlip, endAngle);
                    tongueRect.y += tongueRect.h;
                    break;
                default:
                    break;
                }
            }
            //Renderizamos punta de la lengua
            tongueText->renderFrameWithFlip(tongueRect, 1, 0, endFlip, endAngle);
        }
    }

    //renderizamos la rana
    frogRect.w = size;
    frogRect.h = size;

    if (frogAnimator->getCurrentAnim().flip) //Si se tiene que flipear
        frogText->renderFrameWithFlip(frogRect, frogAnimator->getCurrentFil(), frogAnimator->getCurrentCol(), SDL_FLIP_HORIZONTAL, 0);
    else
        frogText->renderFrame(frogRect, frogAnimator->getCurrentFil(), frogAnimator->getCurrentCol());
}

void RenderComponentFrog::AttackStart() {
    attacking = true;
}
