#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <functional>
#include "TransformComponent.h"

class Collider {
public:
	Collider(Box* box) : funciones(std::list<void(*)(Entity*)>()), box(box) {
		
	};
	//Añade una funcion al collider que quieras
	void AddCall(void(*)(Entity*));
	//Comprueba la colision con un collider, si hay colision llama a OnCollision
	void OnCollision(Entity* e);
	bool Collides(Collider) const;
private:
	Box* box; //La caja que define el tamaño y posicion del collider
	//El box tiene que ser gestionado por el creador del box
	std::list<void(*)(Entity*)> funciones; //Las funciones a llamar en caso de colision
};

//Comprueba colisiones de objetos, y envía un mensaje con la información relevante a los componentes suscritos
//NUEVA VERSION: El collider component puede tener varios colliders. Uno siempre que va a estar establecido por el transform.
//La entidad puede tener mas cajas de colisiones, que se deberán añadir desde otros componentes. Estas tienen una posición relativa al transform.
class ColliderComponent : public Component
{
public:
	ColliderComponent() : colliders(std::list<Collider>()) {};
	ColliderComponent(TransformComponent* tr) : colliders(std::list<Collider>()) {
		AddCollider(Collider(tr));
	};
	//Comprueba la colisión de los colliders de este componente con los de la otra entidad
	void CheckCollision(Entity* e);
	//Añade un collider a este componente
	void AddCollider(Collider c);
	std::list<Collider> GetColliders() const;
	
private:
	//Lista de colliders gestionados por este componente
	std::list<Collider> colliders;
};

