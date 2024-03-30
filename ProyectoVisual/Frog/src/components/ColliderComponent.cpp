#include "ColliderComponent.h"

bool ColliderComponent::CheckCollision(Entity* e) {
	
}

void ColliderComponent::AddCall(std::function<void()>* func) {
	funcion = func;
}

void ColliderComponent::OnCollision() {
	//Esto llama a la funcion guardada 
	if(funcion != nullptr)
		(*funcion)();
}