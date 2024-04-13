#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "TransformComponent.h"
#include "AnimationComponent.h"
/*
* Se encargará de renderizar cada entidad en la ubicación de la pantalla acorde al tilemap
*/
class RenderComponent :	public Component
{
protected:
	Texture* myTexture;
	AnimationComponent* myAnimator;
	TransformComponent* transform;
	float scale;

public: 
	//Constructora con animador
	RenderComponent(Texture* tex, int wframes, int hframes, float sc, AnimationComponent* anim);
	//Constructora sin animador
	RenderComponent(Texture* tex, int wframes, int hframes, float sc);
	RenderComponent(Texture* t, float);
	Texture* GetTexture() { return myTexture; };
    void render();
	void initComponent() override;
};