#include "ColliderComponent.h"
#include <SDL.h>
#include "MovementComponent.h"
#include "RenderComponent.h"
#include "RenderComponentFrog.h"

bool ColliderComponent::CheckCollision(Entity* e) {
	//Habra que cambiar cosas cuando esté el transform
	MovementComponent* mc = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT));
	Texture* t = ent->getRenderComponentFrog()->getFrogText();
	SDL_Rect miRect = {
		mc->getPosition().getX(),
		mc->getPosition().getY(),
		t->width(),
		t->height()
	};
	mc = static_cast<MovementComponent*>(e->getComponent(MOVEMENT_COMPONENT));
	t = e->getRenderComponent()->GetTexture();
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

