#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
class TransformComponent;

class RenderComponentFrog : public Component
{
private:
	Texture* frogText ;
	Texture* tongueText ;
	AnimationComponent* frogAnimator ;
	TransformComponent* transform;
	float scale;
	bool attacking;
public:
	RenderComponentFrog(Texture* tf, Texture* tt, AnimationComponent* animFrog, float sc = 1) :
		frogText(tf), tongueText(tt), 
		frogAnimator(animFrog), 
		transform(nullptr),
		scale(sc),attacking(false) {
	};
	~RenderComponentFrog() {
		tongueText= nullptr;
		frogText = nullptr;
		//delete frogText;
	};
	void render();
	void AttackStart();
	
	Texture* getFrogText() {
		return frogText;
	}

	void initComponent() override;
};

