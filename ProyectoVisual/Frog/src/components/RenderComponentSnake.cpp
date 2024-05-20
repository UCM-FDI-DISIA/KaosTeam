#include "../scenes/RoomScene.h"
#include "../managers/MapManager.h"
#include "AttackComponentSnake.h"
#include "RenderComponentSnake.h"
#include "AnimationComponent.h"
#include "TransformComponent.h"

void RenderComponentSnake::render() {
    int t = ent->getScene()->getMapReader()->getTileSize();
    int size = t * scale;
    SDL_Rect snakeRect;
    SDL_Rect neckRect;                         

    Vector2D offset = transform->getOffset()                      
                     + Vector2D((t - size) / 2, (t - size) / 2); 
    Vector2D pos = transform->getCasilla();
    Direction d = static_cast<MovementComponentSnake*>(ent->getComponent(MOVEMENT_COMPONENT))->getDirection(); //Obtenemos direccion actual
    Vector2D cameraPos = Camera::instance()->getCameraMovement();


    snakeRect.x = pos.getX() * t + offset.getX() - cameraPos.getX();
    snakeRect.y = pos.getY() * t + offset.getY() - cameraPos.getY();
    snakeRect.w = size;
    snakeRect.h = size;

    //el cuello de la serpiente
    if (attacking) {
        int distanceMoved = static_cast<AttackComponentSnake*>(ent->getComponent(ATTACK_COMPONENT))->getDistanceMoved();
        Vector2D tongueEndPos = pos;

        if (distanceMoved < 0) {
            attacking = false;
            switch (d) {
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
        else { 
            neckRect.h = size;
            neckRect.w = t;
            neckRect.y = snakeRect.y;
            neckRect.x = snakeRect.x + size / 2;

            float endAngle = 0.0f;
            SDL_RendererFlip endFlip = SDL_FLIP_NONE;

            switch (d) {
            case Direction::LEFT_ROT:
                neckRect.x = snakeRect.x - size / 2;
                endFlip = SDL_FLIP_HORIZONTAL;
                tongueEndPos.setX(tongueEndPos.getX() - distanceMoved);
                break;
            case Direction::RIGHT_ROT:
                neckRect.x = snakeRect.x + size / 2;
                tongueEndPos.setX(tongueEndPos.getX() + distanceMoved);
                break;
            case Direction::UP_ROT:
                neckRect.y = snakeRect.y - size / 2;
                neckRect.x = snakeRect.x + 5;
                endAngle = -90.0f;
                tongueEndPos.setY(tongueEndPos.getY() - distanceMoved);
                break;
            case Direction::DOWN_ROT:
                snakeAnimator->playAnimation("ATTACK_DOWN");
                myTexture->renderFrame(snakeRect, snakeAnimator->getCurrentFil(), snakeAnimator->getCurrentCol());
                neckRect.y = snakeRect.y + size / 2;
                neckRect.x = snakeRect.x - 5;
                endAngle = 90.0f;
                tongueEndPos.setY(tongueEndPos.getY() + distanceMoved);
                break;
            default:
                break;
            }
            for (int i = 0; i < distanceMoved; i++) {
                switch (d) {
                case Direction::LEFT_ROT:
                    snakeAnimator->playAnimation("ATTACK_LEFT");
                    neckTexture->renderFrameWithFlip(neckRect, 0, 0, endFlip, endAngle);
                    neckRect.x -= neckRect.w;
                    break;
                case Direction::RIGHT_ROT:
                    snakeAnimator->playAnimation("ATTACK_RIGHT");
                    neckTexture->renderFrameWithFlip(neckRect, 0, 0, endFlip, endAngle);
                    neckRect.x += neckRect.w;
                    break;
                case Direction::UP_ROT:
                    snakeAnimator->playAnimation("ATTACK_UP");
                    neckTexture->renderFrameWithFlip(neckRect, 0, 0, endFlip, endAngle);
                    neckRect.y -= neckRect.h;
                    break;
                case Direction::DOWN_ROT:
                    neckTexture->renderFrameWithFlip(neckRect, 0, 0, endFlip, endAngle);
                    neckRect.y += neckRect.h;
                    break;
                default:
                    break;
                }
            }
            static_cast<AttackComponentSnake*>(ent->getComponent(ATTACK_COMPONENT))->UpdateBox(tongueEndPos, neckRect.w, neckRect.h);
            neckTexture->renderFrameWithFlip(neckRect, 1, 0, endFlip, endAngle);
        }
    }

    switch (d) {
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
    if (snakeAnimator->getCurrentAnim().flipHorizontal) //si se flipea la animacion
        myTexture->renderFrameWithFlip(snakeRect, snakeAnimator->getCurrentFil(), snakeAnimator->getCurrentCol(), SDL_FLIP_HORIZONTAL, 0);
    else
        myTexture->renderFrame(snakeRect, snakeAnimator->getCurrentFil(), snakeAnimator->getCurrentCol());
}

void RenderComponentSnake::AttackStart() {
    attacking = true;
}

void RenderComponentSnake::initComponent() {
    transform = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
}
