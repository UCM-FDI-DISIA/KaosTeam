#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <functional>
#include "TransformComponent.h"

class Collider {
	Collider(Box box) : funciones(std::list<std::function<void(Entity*)>*>()), box(box) {};
	Box box; //La caja que define el tamaño y posicion del collider
	std::list<std::function<void(Entity*)>*> funciones; //Las funciones a llamar en caso de colision

};

//Comprueba colisiones de objetos, y envía un mensaje con la información relevante a los componentes suscritos
//NUEVA VERSION: El collider component puede tener varios colliders. Uno siempre que va a estar establecido por el transform.
//La entidad puede tener mas cajas de colisiones, que se deberán añadir desde otros componentes. Estas tienen una posición relativa al transform.
class ColliderComponent : public Component
{
public:
	ColliderComponent() : colliders(std::list<Collider>()) {};
	~ColliderComponent() {
		//No hay que eliminar function porque pertenece al objeto llamado
	};
	//Comprueba la colisión de los colliders de este componente con los de la otra entidad
	bool CheckCollision(Entity* e);
	//A llamar en caso de colisión, como parametro la entidad colisionada
	void OnCollision(Entity* e);

	//Añade una funciona al collider que quieras
	void AddCall(std::function<void(Entity* e)>* func);
private:
	//Lista de colliders gestionados por este componente
	std::list<Collider> colliders; 
};

