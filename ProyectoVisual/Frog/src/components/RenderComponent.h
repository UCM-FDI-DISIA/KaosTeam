#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"


/*
* Se encargará de renderizar cada entidad en la ubicación de la pantalla acorde al tilemap
*/
class RenderComponent :public Component
{
protected:
	Texture* myTexture = nullptr;
	AnimationComponent* myAnimator = nullptr;
	float scale;

public:
	RenderComponent(Texture* tex, int wframes, int hframes, float sc, AnimationComponent* anim) : myTexture(tex), scale(sc), myAnimator(anim) {};
	RenderComponent(Texture* t, float sc = 1) : myTexture(t), scale(sc) {}
    void render();
};