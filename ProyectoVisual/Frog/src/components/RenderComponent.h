#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "TransformComponent.h"
/*
* Se encargar� de renderizar cada entidad en la ubicaci�n de la pantalla acorde al tilemap
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
	RenderComponent(Texture* tex, int wframes, int hframes, float sc) : myTexture(tex), scale(sc) {};
	RenderComponent(Texture* t, float sc = 1) : myTexture(t), scale(sc) { };
	~RenderComponent() {};
	Texture* GetTexture() const { return myTexture; };
	//Por si queremos cambiar la textura a un objeto
	void ChangeTexture(Texture* newText) { myTexture = newText; };
    void render();
	virtual void initComponent() override;
};