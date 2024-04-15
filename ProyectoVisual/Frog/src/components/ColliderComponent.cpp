#include "ColliderComponent.h"
#include <SDL.h>
#include "TransformComponent.h"
/*
	Comprueba si tiene colisi�n con la entidad e.
	En caso de que le entidad tenga collider, no sea ella misma y se est� tocando devuelve true.
*/

//Amplicaci�n: el componente puede tener varias "cajas" de colisi�n. Es decir, no solo puedes utilizar el transform como caja de colisi�n, sino otra.

bool ColliderComponent::CheckCollision(Entity* e) {
	//Habra que cambiar cosas cuando est� el transform
	if (e != ent) {
		SDL_Rect suRect = static_cast<TransformComponent*>(e->getComponent(TRANSFORM_COMPONENT))->GetOnDisplayPosition();
		SDL_Rect miRect = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT))->GetOnDisplayPosition();

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