#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

//Comprueba colisiones de objetos, y env�a un mensaje con la informaci�n relevante a los componentes suscritos
//La llamada a comporbar colisiones debe hacerse en el update del room antes o despu�s del update de las entidades
class ColliderComponent : public Component
{
public:
	ColliderComponent() {};
	~ColliderComponent() {};
private:

};

