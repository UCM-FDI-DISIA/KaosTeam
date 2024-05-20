#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <functional>
#include "TransformComponent.h"

/*Si quieres identificar un tipo específico de collider, puedes darle uno de los siguientes tipos
Podeos añadir nuevos si es necesario*/
enum ColliderName {
	UNAMED_COLLIDER,
	TONGUE_COLLIDER,
	TRANSFORM_COLLIDER
};

/*Define un elemento con el que se puede colisionar. Son gestionador por el ColliderComponent.
Necesitan una box que defina el espacion en pantalla que ocupan*/
class Collider {
public:
	Collider(Box* box, ColliderName name) : funciones(std::list<std::function<void(Entity*, Collider)>>()), box(box), name(name) {};
	//En caso de no querer darle un ColliderName. Lo deja como UNAMED_COLLIDER
	Collider(Box* box) : funciones(std::list<std::function<void(Entity*, Collider)>>()), box(box), name(UNAMED_COLLIDER) {};
	//Añade una funcion al collider que quieras
	void AddCall(std::function<void(Entity*, Collider)> func);
	//Método a llamar cuando hay colision. Recibe la entidad y el Collider colisionado. Llama a todos los métodos añadidoss al collider.
	void OnCollision(Entity*, Collider);
	//Comprueba la colisión de este collider con otro. Devuelve true si hay colisión.
	bool Collides(Collider) const;

	void deleteBox()
	{
		if (box != nullptr)
		delete box;
	}
	
	ColliderName getName() const;
	Box* GetBox() const { return box; };

private:
	Box* box; //La caja que define el tamaño y posicion del collider, tiene que ser gestionado por el creador del box
	std::list<std::function<void(Entity*, Collider)>> funciones; //Las funciones a llamar en caso de colision
	ColliderName name; //El tipo de este collider
};

//Comprueba colisiones de objetos, y envía un mensaje con la información relevante a los componentes suscritos
//NUEVA VERSION: El collider component puede tener varios colliders. Uno siempre que va a estar establecido por el transform.
//La entidad puede tener mas cajas de colisiones, que se deberán añadir desde otros componentes. Estas tienen una posición relativa al transform.
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
	~ColliderComponent();
	//Comprueba la colisión de los colliders de este componente con los de la otra entidad
	void CheckCollision(Entity* e);
	//Añade un collider a este componente
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

