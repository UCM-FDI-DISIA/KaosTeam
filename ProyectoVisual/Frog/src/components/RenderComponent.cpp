#include "RenderComponent.h"
#include "../scenes/RoomScene.h"

RenderComponent::RenderComponent(Texture* tex, int wframes, int hframes, float sc, AnimationComponent* anim) :
	myTexture(tex), scale(sc), myAnimator(anim), transform(nullptr) {};

RenderComponent::RenderComponent(Texture* tex, int wframes, int hframes, float sc) :
	myTexture(tex), scale(sc), myAnimator(nullptr), transform(nullptr) {};

RenderComponent::RenderComponent(Texture* t, float sc = 1) :
	myTexture(t), scale(sc), myAnimator(nullptr), transform(nullptr) { };

void RenderComponent::render()
{
	if (myAnimator == nullptr)//si no tiene animator
	{
		myTexture->render(transform->GetOnDisplayPosition());
	}
	else {
		//segun si necesita flip o no la textura
		if (myAnimator->getCurrentAnim().flip) {
			myTexture->renderFrameWithFlip(transform->GetOnDisplayPosition(), myAnimator->getCurrentFil(), myAnimator->getCurrentCol(), SDL_FLIP_HORIZONTAL, 0);
		}
		else {
			myTexture->renderFrame(transform->GetOnDisplayPosition(), myAnimator->getCurrentFil(), myAnimator->getCurrentCol());
		}
	}
}

void RenderComponent::initComponent() {
	transform = ent->getComponent<TransformComponent>(TRANSFORM_COMPONENT);
}