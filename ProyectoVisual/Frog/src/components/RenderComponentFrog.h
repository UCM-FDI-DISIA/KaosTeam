#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
class RenderComponentFrog: public Component
{
private:
	//SDL_Rect tongueRect;
	Texture* frogText = nullptr;
	Texture* tongueText = nullptr;
	AnimationComponent* frogAnimator = nullptr;
	float scale;
	bool attacking = false;
	//enum direction { LEFT, RIGHT, UP, DOWN };
public:
	RenderComponentFrog(Texture* tf, Texture* tt, AnimationComponent* animFrog, float sc = 1) :
		frogText(tf), tongueText(tt), 
		frogAnimator(animFrog), 
		scale(sc) {};
	~RenderComponentFrog() {
		delete tongueText;
		delete frogText;
	};
	void render();
	void AttackStart();
};

