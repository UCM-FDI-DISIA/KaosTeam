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
		SDL_Rect suRect = e->getComponent<TransformComponent>(TRANSFORM_COMPONENT)->GetOnDisplayPosition();
		SDL_Rect miRect = ent->getComponent<TransformComponent>(TRANSFORM_COMPONENT)->GetOnDisplayPosition();

		return SDL_HasIntersection(&miRect, &suRect);
	}
	return false;
}

void ColliderComponent::AddCall(std::function<void(Entity*)>* func) {
	funciones.push_back(func);
}

void ColliderComponent::OnCollision(Entity* e) {
	//Esto llama a las funciones guardadas 
	for (std::function<void(Entity*)>* func : funciones) {
		(*func)(e);
	}
}