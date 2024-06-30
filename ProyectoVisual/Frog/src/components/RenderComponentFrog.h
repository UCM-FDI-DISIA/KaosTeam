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
	bool defending;
	bool throwing; //Se usa en caso de que se lance un objeto
	int tongueTipSheetId = 1; //La punta default (sin gancho)

public:
	RenderComponentFrog(Texture* tf, Texture* tt, AnimationComponent* animFrog, float sc = 1) :
		frogText(tf), tongueText(tt),
		frogAnimator(animFrog),
		transform(nullptr),
		scale(sc), attacking(false), throwing(false) {
	};
	~RenderComponentFrog() {
		tongueText= nullptr;
		frogText = nullptr;
		//delete frogText;
	};
	void render();
	void AttackStart(bool withHook = false);
	void DefenseStart();
	void ThrowStart();
	void IdleStart();
	
	Texture* getFrogText() {
		return frogText;
	}

	void initComponent() override;
};

