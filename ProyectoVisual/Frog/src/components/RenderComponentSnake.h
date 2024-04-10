#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/MovementComponentFrog.h"

class TransformComponent;

class RenderComponentSnake : public Component {
private:
	Texture* snakeText = nullptr;
	Texture* tongueText = nullptr;
	AnimationComponent* snakeAnimator = nullptr;
	TransformComponent* transform = nullptr;
	float scale;
	bool attacking = false;
public:
	RenderComponentSnake(Texture* ts, Texture* tt, AnimationComponent* animSnake, float sc = 1) :
		snakeText(ts), tongueText(tt),
		snakeAnimator(animSnake),
		scale(sc){};
	~RenderComponentSnake() {
		delete tongueText;
		delete snakeText;
	};
	void render();
	void AttackStart();

	Texture* getFrogText() {
		return snakeText;
	}

	//Esto está aquí de manera provisional
	SDL_Rect GetOnDisplayPosition();
};

