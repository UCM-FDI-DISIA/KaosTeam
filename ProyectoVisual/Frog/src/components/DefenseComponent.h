#pragma once
#include "../ecs/Component.h"
#include "../managers/InputManager.h"

class Entity;
class Box;
class DefenseComponent : public Component
{
private:
	bool defenseActive = false;
	int defenseTime,			// constante de tiempo que dura la defensa
		timeSinceChange,		// tiempo desde la ultima vez que cambio de modo defensa/normal
		defenseCooldown;		// constante de tiempo que 
	InputManager* inputM;

public:
	DefenseComponent();
	void update() override;
	bool otherStatesChecker();
};