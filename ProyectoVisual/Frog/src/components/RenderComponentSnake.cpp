#include "RenderComponentSnake.h"
#include "../scenes/RoomScene.h"
#include "../managers/MapManager.h"
#include "AttackComponentSnake.h"
#include "MovementComponentSnake.h"
#include "AnimationComponent.h"
#include "TransformComponent.h"

void RenderComponentSnake::render() {
    int t = ent->getScene()->getMapReader()->getTileSize();
    int size = (int)t * scale;
    SDL_Rect frogRect; // Rect de la rana
    SDL_Rect tongueRect;                         

    Vector2D offset = transform->getOffset()                      //el offset el objeto
                     + Vector2D((t - size) / 2, (t - size) / 2);  //para que este centrado en la casilla
    Vector2D pos = transform->getCasilla();
    Direction d = static_cast<MovementComponentSnake*> (ent->getComponent(MOVEMENT_COMPONENT))->getDirection(); //Obtenemos direccion actual
    Vector2D cameraPos = Camera::instance()->getCameraMovement();


    frogRect.x = pos.getX() * t + offset.getX() - cameraPos.getX();
    frogRect.y = pos.getY() * t + offset.getY() - cameraPos.getY();
    frogRect.w = size;
    frogRect.h = size;

    //el cuello de la serpiente
    if (attacking) {
        int distanceMoved = static_cast<AttackComponentFrog*>(ent->getComponent(ATTACK_COMPONENT))->getDistanceMoved();
        Vector2D tongueEndPos = pos;

        if (distanceMoved < 0) { //Si el ataque acaba
            attacking = false;
            switch (d) { //Se reproduce el idle correspondiente
            case Direction::LEFT_ROT:
                snakeAnimator->playAnimation("IDLE_LEFT");
                break;
            case Direction::RIGHT_ROT:
                snakeAnimator->playAnimation("IDLE_RIGHT");
                break;
            case Direction::UP_ROT:
                snakeAnimator->playAnimation("IDLE_UP");
                break;
            case Direction::DOWN_ROT:
                snakeAnimator->playAnimation("IDLE_DOWN");
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
            case Direction::LEFT_ROT:
                tongueRect.x = frogRect.x - size / 2;
                endFlip = SDL_FLIP_HORIZONTAL;
                tongueEndPos.setX(tongueEndPos.getX() - distanceMoved);
                break;
            case Direction::RIGHT_ROT:
                tongueRect.x = frogRect.x + size / 2;
                tongueEndPos.setX(tongueEndPos.getX() + distanceMoved);
                break;
            case Direction::UP_ROT:
                tongueRect.y = frogRect.y - size / 2;
                tongueRect.x = frogRect.x + 5;
                endAngle = -90.0f;
                tongueEndPos.setY(tongueEndPos.getY() - distanceMoved);
                break;
            case Direction::DOWN_ROT:
                snakeAnimator->playAnimation("ATTACK_DOWN");
                myTexture->renderFrame(frogRect, snakeAnimator->getCurrentFil(), snakeAnimator->getCurrentCol());
                tongueRect.y = frogRect.y + size / 2;
                tongueRect.x = frogRect.x - 5;
                endAngle = 90.0f;
                tongueEndPos.setY(tongueEndPos.getY() + distanceMoved);
                break;
            default:
                break;
            }
            for (int i = 0; i < distanceMoved; i++) {
                switch (d) { //Dependiendo de la direccion, la lengua se alarga en una dir u otra
                case Direction::LEFT_ROT:
                    snakeAnimator->playAnimation("ATTACK_LEFT");
                    tongueText->renderFrameWithFlip(tongueRect, 0, 0, endFlip, endAngle);
                    tongueRect.x -= tongueRect.w;
                    break;
                case Direction::RIGHT_ROT:
                    snakeAnimator->playAnimation("ATTACK_RIGHT");
                    tongueText->renderFrameWithFlip(tongueRect, 0, 0, endFlip, endAngle);
                    tongueRect.x += tongueRect.w;
                    break;
                case Direction::UP_ROT:
                    snakeAnimator->playAnimation("ATTACK_UP");
                    tongueText->renderFrameWithFlip(tongueRect, 0, 0, endFlip, endAngle);
                    tongueRect.y -= tongueRect.h;
                    break;
                case Direction::DOWN_ROT:
                    //la rana se renderiza antes en este caso particular
                    tongueText->renderFrameWithFlip(tongueRect, 0, 0, endFlip, endAngle);
                    tongueRect.y += tongueRect.h;
                    break;
                default:
                    break;
                }
            }
            //Renderizamos punta de la lengua
            static_cast<AttackComponentSnake*>(ent->getComponent(ATTACK_COMPONENT))->UpdateBox(tongueEndPos, tongueRect.w, tongueRect.h);

            tongueText->renderFrameWithFlip(tongueRect, 1, 0, endFlip, endAngle);
        }
    }

    switch (d) { //Se reproduce el idle correspondiente
    case Direction::LEFT_ROT:
        snakeAnimator->playAnimation("IDLE_LEFT");
        break;
    case Direction::RIGHT_ROT:
        snakeAnimator->playAnimation("IDLE_RIGHT");
        break;
    case Direction::UP_ROT:
        snakeAnimator->playAnimation("IDLE_UP");
        break;
    case Direction::DOWN_ROT:
        snakeAnimator->playAnimation("IDLE_DOWN");
        break;
    default:
        break;
    }

    //renderizamos la serpiente (depues de la lengua si no mira hacia abajo en el ataque)
    //if (d != DOWN || !attacking)
    //{
    if (snakeAnimator->getCurrentAnim().flip) //Si se tiene que flipear
        myTexture->renderFrameWithFlip(frogRect, snakeAnimator->getCurrentFil(), snakeAnimator->getCurrentCol(), SDL_FLIP_HORIZONTAL, 0);
    else
        myTexture->renderFrame(frogRect, snakeAnimator->getCurrentFil(), snakeAnimator->getCurrentCol());
    //}
}

void RenderComponentSnake::AttackStart() {
    attacking = true;
}

void RenderComponentSnake::initComponent() {
    transform = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
}
