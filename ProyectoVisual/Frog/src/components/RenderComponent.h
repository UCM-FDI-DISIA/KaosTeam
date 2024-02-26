#pragma once
#include "../ecs/Component.h"
#include "MovementComponent.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"


/*
* Se encargará de renderizar cada entidad en la ubicación de la pantalla acorde al tilemap
*/
class RenderComponent :public Component
{
private:
	Texture* myTexture = nullptr;
	float scale;

public:
	RenderComponent() {};
	RenderComponent(std::string filename, int wframes, int hframes, float sc = 1): scale (sc){
		myTexture = new Texture(sdlutils().renderer(), filename, wframes, hframes);
	};

	void render();
	virtual void Update() {};
};