#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

//Comprueba colisiones de objetos, y envía un mensaje con la información relevante a los componentes suscritos
//La llamada a comporbar colisiones debe hacerse en el update del room antes o después del update de las entidades
class ColliderComponent : public Component
{
public:
	ColliderComponent() {};
	~ColliderComponent() {};
private:

};

