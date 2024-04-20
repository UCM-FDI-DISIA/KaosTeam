#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/MovementComponentFrog.h"

class TransformComponent;

class RenderComponentSnake : public Component {
private:
	Texture* snakeText;
	Texture* tongueText;
	AnimationComponent* snakeAnimator;
	TransformComponent* transform;
	float scale;
	bool attacking = false;
public:
	RenderComponentSnake(Texture* ts, Texture* tt, AnimationComponent* animSnake, float sc = 1) :
		snakeText(ts), tongueText(tt),
		snakeAnimator(animSnake),
		scale(sc),transform(nullptr){};
	~RenderComponentSnake() {
		tongueText=nullptr;
		snakeText=nullptr;
	};
	void render();
	void AttackStart();

	Texture* getFrogText() {
		return snakeText;
	}

	void initComponent() override;
	//Esto está aquí de manera provisional
	SDL_Rect GetOnDisplayPosition();
};

