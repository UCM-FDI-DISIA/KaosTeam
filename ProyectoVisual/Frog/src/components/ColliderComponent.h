#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <functional>

//Comprueba colisiones de objetos, y env�a un mensaje con la informaci�n relevante a los componentes suscritos
//NUEVA VERSION: El collider component puede tener varios colliders. Uno siempre que va a estar establecido por el transform.
//La entidad puede tener mas cajas de colisiones, que se deber�n a�adir desde otros componentes.
class ColliderComponent : public Component
{
public:
	ColliderComponent() : funciones(std::list<std::function<void(Entity*)>*>()) {};
	~ColliderComponent() {
		//No hay que eliminar function porque pertenece al objeto llamado
	};
	//Comprueba la colisi�n con la estidad e
	bool CheckCollision(Entity* e);
	//A llamar en caso de colisi�n, como parametro la entidad colisionada
	void OnCollision(Entity* e);

	//A�ade una funciona al collider que quieras
	void AddCall(std::function<void(Entity* e)>* func);
private:
	//Lista de funciones a llamar cuando se detecta la colisi�n
	std::list<std::function<void(Entity*)>*> funciones;
};

