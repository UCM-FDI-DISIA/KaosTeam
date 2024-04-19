#include "ColliderComponent.h"
#include <SDL.h>
#include "TransformComponent.h"
/*
	Comprueba si tiene colisión con la entidad e.
	En caso de que le entidad tenga collider, no sea ella misma y se esté tocando devuelve true.
*/

void ColliderComponent::CheckCollision(Entity* e) {
	//Comprueba los colliders de este ColliderComponent con los colliders del otro
	if (e != ent) {
		ColliderComponent* coll2 = static_cast<ColliderComponent*>(e->getComponent(COLLIDER_COMPONENT));
		if (coll2 != nullptr) {
			std::list<Collider> colliders2 = coll2->GetColliders();
			for (Collider collider : colliders) {
				for (Collider collider2 : colliders2) {
					if (collider.Collides(collider2))
						collider2.OnCollision(ent);
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
void Collider::AddCall(void(*func)(Entity*)) {
	funciones.push_back(func);
}

void Collider::OnCollision(Entity* e) {
	//Esto llama a las funciones guardadas
	for (std::function<void(Entity*)> func : funciones) {
		(func)(e);
	}
}

bool Collider::Collides(Collider c) const{
	SDL_Rect suRect = c.box->GetOnDisplayPosition();
	SDL_Rect miRect = box->GetOnDisplayPosition();

	return SDL_HasIntersection(&miRect, &suRect);
}

Collider* ColliderComponent::GetTransofmCollider() {
	return transformCollider;
}