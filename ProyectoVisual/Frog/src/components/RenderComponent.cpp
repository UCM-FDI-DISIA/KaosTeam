#include "RenderComponent.h"
#include "../scenes/RoomScene.h"


void RenderComponent::render()
{
	//segun si necesita flip o no la textura
	if (myAnimator != nullptr) {
		if (myAnimator->getCurrentAnim().flip) {
			myTexture->renderFrameWithFlip(transform->GetOnDisplayPosition(), myAnimator->getCurrentFil(), myAnimator->getCurrentCol(), SDL_FLIP_HORIZONTAL, 0);
		}
		else {
			myTexture->renderFrame(transform->GetOnDisplayPosition(), myAnimator->getCurrentFil(), myAnimator->getCurrentCol());
		}	
	}
	else {
		myTexture->render(transform->GetOnDisplayPosition());
	}
}

void RenderComponent::initComponent() {
	transform = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
	myAnimator = static_cast<AnimationComponent*>(ent->getComponent(ANIMATION_COMPONENT));
}