#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <functional>
#include "TransformComponent.h"

enum ColliderName {
	UNAMED_COLLIDER,
	ENEMY_COLLIDER,
	FROG_COLLIDER,
	TRANSFORM_COLLIDER
};

class Collider {
public:
	Collider(Box* box, ColliderName name) : funciones(std::list<std::function<void(Entity*, Collider)>>()), box(box), name(name) {};
	Collider(Box* box) : funciones(std::list<std::function<void(Entity*, Collider)>>()), box(box), name(UNAMED_COLLIDER) {};
	//A�ade una funcion al collider que quieras
	void AddCall(std::function<void(Entity*, Collider)> func);
	//Comprueba la colision con un collider, si hay colision llama a OnCollision
	void OnCollision(Entity* e, Collider);
	bool Collides(Collider) const;
	ColliderName getName() const;
private:
	Box* box; //La caja que define el tama�o y posicion del collider
	//El box tiene que ser gestionado por el creador del box
	std::list<std::function<void(Entity*, Collider)>> funciones; //Las funciones a llamar en caso de colision
	ColliderName name;
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
	//Te crea un collider con el transform. Se puede pillar con GetTransformCollider
	ColliderComponent(TransformComponent* tr) : colliders(std::list<Collider>()) {
		AddCollider(Collider(tr, TRANSFORM_COLLIDER));
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

