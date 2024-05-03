#include "../ecs/Component.h"

/*Inlcuye: Mejoras permanentes de salto, vida m�xima, da�o y alcance de ataque.
Adem�s de las habilidades desbloqueables como el gancho, y la bolsa para explosivos */
class MejoraComponent : public Component
{
	//Define cada mejora y habilidad extra
	enum Mejora {
		GANCHO,
		SACO_BOMBAS,
		SALTAMONTES,
		MOSCAS_VIDA,
		AVISPAS,
		CIEMPIES
		};
};