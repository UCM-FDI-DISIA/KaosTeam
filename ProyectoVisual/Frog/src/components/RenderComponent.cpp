#include "RenderComponent.h"
#include "../scenes/RoomScene.h"


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

void RenderComponent::changeAlpha(int newAlpha)
{
	SDL_SetTextureAlphaMod(myTexture->getTexture(), newAlpha);
}

void RenderComponent::initComponent() {
	transform = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
	myAnimator = static_cast<AnimationComponent*>(ent->getComponent(ANIMATION_COMPONENT));
}