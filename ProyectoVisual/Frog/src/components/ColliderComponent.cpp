#include "ColliderComponent.h"
#include <SDL.h>
#include "MovementComponent.h"
#include "RenderComponent.h"

bool ColliderComponent::CheckCollision(Entity* e) {
	//Habra que cambiar cosas cuando esté el transform
	MovementComponent* mc = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT));
	Texture* t = static_cast<RenderComponent*>(ent->getComponent(RENDER_COMPONENT))->GetTexture();
	SDL_Rect miRect = {
		mc->getPosition().getX(),
		mc->getPosition().getY(),
		t->width(),
		t->height()
	};
	mc = static_cast<MovementComponent*>(e->getComponent(MOVEMENT_COMPONENT));
	t = static_cast<RenderComponent*>(e->getComponent(RENDER_COMPONENT))->GetTexture();
	SDL_Rect suRect = {
		mc->getPosition().getX(),
		mc->getPosition().getY(),
		t->width(),
		t->height()
	};

	return SDL_HasIntersection(&miRect, &suRect);
}

void ColliderComponent::AddCall(std::function<void()>* func) {
	funcion = func;
}

void ColliderComponent::OnCollision() {
	//Esto llama a la funcion guardada 
	if(funcion != nullptr)
		(*funcion)();
}

