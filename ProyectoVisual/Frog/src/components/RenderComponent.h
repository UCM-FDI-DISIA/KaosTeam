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

public: 
	RenderComponent(Texture* tex) : myTexture(tex), myAnimator(nullptr), transform(nullptr) {};
	Texture* GetTexture() const { return myTexture; };
	void ChangeTexture(Texture* newText) { myTexture = newText; }; //Por si queremos cambiar la textura a un objeto
    void render();
	void initComponent() override;
};