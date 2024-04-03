#include "ColliderComponent.h"
#include <SDL.h>
#include "TransformComponent.h"
/*
	Comprueba si tiene colisión con la entidad e.
	En caso de que le entidad tenga collider, no sea ella misma y se esté tocando devuelve true.
*/
bool ColliderComponent::CheckCollision(Entity* e) {
	//Habra que cambiar cosas cuando esté el transform
	if (e != ent) {
		SDL_Rect suRect = static_cast<TransformComponent*>(e->getComponent(TRANSFORM_COMPONENT))->GetOnDisplayPosition();
		SDL_Rect miRect = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT))->GetOnDisplayPosition();

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