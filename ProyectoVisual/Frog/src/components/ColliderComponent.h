#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <functional>
#include "TransformComponent.h"

class Collider {
public:
	Collider(Box* box) : funciones(std::list<std::function<void(Entity*)>>()), box(box) {};
	//A�ade una funcion al collider que quieras
	void AddCall(std::function<void(Entity*)> func);
	//Comprueba la colision con un collider, si hay colision llama a OnCollision
	void OnCollision(Entity* e);
	bool Collides(Collider) const;
private:
	Box* box; //La caja que define el tama�o y posicion del collider
	//El box tiene que ser gestionado por el creador del box
	std::list<std::function<void(Entity*)>> funciones; //Las funciones a llamar en caso de colision
};

//Comprueba colisiones de objetos, y env�a un mensaje con la informaci�n relevante a los componentes suscritos
//NUEVA VERSION: El collider component puede tener varios colliders. Uno siempre que va a estar establecido por el transform.
//La entidad puede tener mas cajas de colisiones, que se deber�n a�adir desde otros componentes. Estas tienen una posici�n relativa al transform.
class ColliderComponent : public Component
{
public:
	ColliderComponent() : colliders(std::list<Collider>()) {
		transformCollider = nullptr;
	};
	ColliderComponent(TransformComponent* tr) : colliders(std::list<Collider>()) {
		AddCollider(Collider(tr));
		transformCollider = &colliders.front();
	};
	//Comprueba la colisi�n de los colliders de este componente con los de la otra entidad
	void CheckCollision(Entity* e);
	//A�ade un collider a este componente
	void AddCollider(Collider c);
	std::list<Collider> GetColliders() const;
	Collider* GetTransofmCollider();
private:
	//Lista de colliders gestionados por este componente
	std::list<Collider> colliders;
	//El collider que tiene transform como Box.
	//Si nullptr, no tiene.
	Collider* transformCollider;
};

