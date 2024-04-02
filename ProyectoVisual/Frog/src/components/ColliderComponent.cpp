#include "ColliderComponent.h"
#include <SDL.h>
#include "MovementComponent.h"
#include "RenderComponent.h"
#include "RenderComponentFrog.h"

/*
	Comprueba si tiene colisión con la entidad e.
	En caso de que le entidad tenga collider, no sea ella misma y se esté tocando devuelve true.
*/
bool ColliderComponent::CheckCollision(Entity* e) {
	//Habra que cambiar cosas cuando esté el transform
	if (e != ent) {
		/*MovementComponent* mc = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT));
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
		};*/
		SDL_Rect suRect = static_cast<RenderComponent*>(e->getRenderComponent())->GetOnDisplayPosition();
		SDL_Rect miRect = static_cast<RenderComponentFrog*>(ent->getRenderComponentFrog())->GetOnDisplayPosition();


		return SDL_HasIntersection(&miRect, &suRect);
	}
	return false;
}

void ColliderComponent::AddCall(std::function<void()>* func) {
	funcion = func;
}

void ColliderComponent::OnCollision() {
	//Esto llama a la funcion guardada 
	if(funcion != nullptr)
		(*funcion)();
}