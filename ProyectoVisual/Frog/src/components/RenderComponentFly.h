#pragma once
#include "AnimationComponent.h"

class RenderComponentFly : public AnimationComponent {
public:
	RenderComponentFly(Texture* flyTex, float sc = 0.5) :AnimationComponent(flyTex, 1, 3, sc) {};
	~RenderComponentFly() {};
	void render() override;
};