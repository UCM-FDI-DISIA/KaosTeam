#pragma once
#include "../ecs/Component.h"
//Esta es una clase para una entidad palanca que al interactuar con ell gancho, este se activar�
//En teor�a cuando el gancho colisiona con una entidad con este componente, 
// el booleano pasa de desactivado a activado
class ObjectLeverComponente : public Component
{
private:
	bool active;
public:
};