#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/MovementComponentFrog.h"
#include "RenderComponent.h";

class TransformComponent;

class RenderComponentSnake : public RenderComponent {
private:
	Texture* neckTexture;
	AnimationComponent* snakeAnimator;
	TransformComponent* transform;
	float scale;
	bool attacking = false;
public:
	RenderComponentSnake(Texture* ts, Texture* tt, AnimationComponent* animSnake, float sc = 1) :
		RenderComponent(ts), neckTexture(tt),
		snakeAnimator(animSnake),
		scale(sc),transform(nullptr){};
	~RenderComponentSnake() {
		neckTexture = nullptr;
		myTexture = nullptr;
	};
	void render();
	void AttackStart();

	Texture* getSnakeText() {
		return myTexture;
	}
	void initComponent() override;
};

