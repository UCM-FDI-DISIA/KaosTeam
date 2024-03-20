#pragma once
#include "RenderComponent.h"
#include "AnimationComponent.h"
class RenderComponentFrog: public AnimationComponent
{
private:
	SDL_Rect tongueRect;
	Texture* tongueText = nullptr;
	bool attacking = false;
	enum direction { LEFT, RIGHT, UP, DOWN };
public:
	RenderComponentFrog(Texture* tf, Texture* tt, float sc = 1) : AnimationComponent(tf, 4, 4, sc), tongueText(tt) {}
	~RenderComponentFrog() { delete tongueText; };
	void render() override;
	void AttackStart();
};

