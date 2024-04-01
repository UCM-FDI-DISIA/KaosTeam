#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"


/*
* Se encargar� de renderizar cada entidad en la ubicaci�n de la pantalla acorde al tilemap
*/
class RenderComponent :public Component
{
protected:
	Texture* myTexture = nullptr;
	AnimationComponent* myAnimator = nullptr;
	float scale;

public: 
	//Constructora con animador
	RenderComponent(Texture* tex, int wframes, int hframes, float sc, AnimationComponent* anim) : myTexture(tex), scale(sc), myAnimator(anim) {};
	//Constructora sin animador
	RenderComponent(Texture* tex, int wframes, int hframes, float sc) : myTexture(tex), scale(sc) {};
	RenderComponent(Texture* t, float sc = 1) : myTexture(t), scale(sc) {}
	Texture* GetTexture() { return myTexture; };
    void render();
	//Obtiene la posici�n en pantalla de la entidad
	//Esto no est� bien aqu�, pero es necesario hasta que haya un transform
	SDL_Rect GetOnDisplayPosition();

};