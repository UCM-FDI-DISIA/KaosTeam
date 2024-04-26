#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
class TransformComponent;

class RenderComponentDestructible
{
private:
	Texture* destrucText = nullptr;
	AnimationComponent* destructAnimator = nullptr;
	TransformComponent* transform = nullptr;
	float scale;
	bool broken = false;
public:
	RenderComponentDestructible(Texture* ts, AnimationComponent* animDestructible, float sc = 1) :
		destrucText(ts),
		destructAnimator(animDestructible),
		scale(sc) {};
	~RenderComponentDestructible() {
		delete destrucText;
	};
	void render();
	void breaking();
};

