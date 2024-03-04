#pragma once
#include "RenderComponent.h"
class RenderComponentFrog: public RenderComponent
{
private:
	SDL_Rect tongueRect;
	Texture* tongueText;

public:
	RenderComponentFrog(Texture* tf, Texture* tt, float sc = 1): RenderComponent(tf, sc), tongueText(tt){}
	~RenderComponentFrog() { delete tongueText; };
	void render() override;
};

