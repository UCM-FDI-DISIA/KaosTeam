#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "TransformComponent.h"
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
	RenderComponent(Texture* tex, int wframes, int hframes, float sc, AnimationComponent* anim) : myTexture(tex), scale(sc), myAnimator(anim), transform(nullptr) {};
	//Constructora sin animador
	RenderComponent(Texture* tex, int wframes, int hframes, float sc) : myTexture(tex), scale(sc), myAnimator(nullptr), transform(nullptr) {};
	RenderComponent(Texture* t, float sc = 1) : myTexture(t), scale(sc), myAnimator(nullptr),transform(nullptr) { };
	virtual ~RenderComponent();
	Texture* GetTexture() { return myTexture; };
    void render();
	void initComponent() override;
};