#pragma once
#include "RenderComponent.h"
#include "AnimationComponent.h"
class RenderComponentFrog: public RenderComponent
{
private:
	SDL_Rect tongueRect;
	Texture* tongueText = nullptr;
	AnimationComponent* myAnim = nullptr;
	bool attacking = false;

public:
	RenderComponentFrog(Texture* tf, Texture* tt, AnimationComponent* a, float sc = 1): RenderComponent(tf, sc), myAnim(a), tongueText(tt){}
	~RenderComponentFrog() { delete tongueText; };
	void render() override;
	void AttackStart();
};

