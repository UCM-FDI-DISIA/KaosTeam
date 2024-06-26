#include "ColliderComponent.h"
#include <SDL.h>
#include "TransformComponent.h"
#include <iostream>
#include "../sdlutils/SDLUtils.h"
/*
	Comprueba si tiene colisi�n con la entidad e.
	En caso de que le entidad tenga collider, no sea ella misma y se est� tocando devuelve true.
*/

ColliderComponent::~ColliderComponent()
{
	for (Collider collider : colliders) {
		if (collider.getName() != TRANSFORM_COLLIDER)
			collider.deleteBox();
	}
	
}

void ColliderComponent::CheckCollision(Entity* e) {
	//Comprueba los colliders de este ColliderComponent con los colliders del otro
	if (e != ent) {
		ColliderComponent* coll2 = static_cast<ColliderComponent*>(e->getComponent(COLLIDER_COMPONENT));
		if (coll2 != nullptr) {
			std::list<Collider> colliders2 = coll2->GetColliders();
			for (Collider collider : colliders) {
   				for (Collider collider2 : colliders2) {
					if (collider.Collides(collider2)) {
						collider2.OnCollision(ent, collider);
					}
				}
			}
		}
	}
}

void ColliderComponent::AddCollider(Collider c) {
	colliders.push_back(c);
}

std::list<Collider> ColliderComponent::GetColliders() const {
	return colliders;
}
void Collider::AddCall(std::function<void(Entity*, Collider)> func) {
	funciones.push_back(func);
}

void Collider::OnCollision(Entity* e, Collider c) {
	//Esto llama a las funciones guardadas
	for (std::function<void(Entity*, Collider)> func : funciones) {
		(func)(e, c);
	}
}

bool Collider::Collides(Collider c) const {
	SDL_Rect suRect = c.box->GetOnDisplayPosition();
	SDL_Rect miRect = box->GetOnDisplayPosition();

	return SDL_HasIntersection(&miRect, &suRect);
}

Collider* ColliderComponent::GetTransformCollider() {
	return transformCollider;
}

ColliderName Collider::getName() const {
	return name;
}