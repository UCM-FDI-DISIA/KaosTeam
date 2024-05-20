#include "DefenseComponent.h"
#include "../ecs/Entity.h"
#include "../managers/DataManager.h"

// faltan animaciones e implementarlo en el da�o
// la idea es que cuando reciba da�o se compruebe el defenseActive y si est� activado no se recibe da�o

void DefenseComponent::update()
{
	if (!otherStatesChecker() && auxInput->getAction1() && (DataManager::GetInstance()->getFrameTime() - timeSinceChange) > defenseCooldown)
	{
		defenseActive = true;
		timeSinceChange = DataManager::GetInstance()->getFrameTime();
	}
	else if (defenseActive && (DataManager::GetInstance()->getFrameTime() - timeSinceChange) > defenseTime)
	{
			defenseActive = false;
			timeSinceChange = DataManager::GetInstance()->getFrameTime();
	}
}

bool DefenseComponent::getDefenseActive()	// getter de defenseActive para comprobar cuando reciba da�o
{
	return defenseActive;
}

bool DefenseComponent::otherStatesChecker()	// comprueba que no haya otras acciones o estados en curso
{
	bool aux = false;

	if(defenseActive)	// a�adir detector de ataque con lengua y ampliar si fuese necesario
	{
		aux = true;
	}

	return aux;
}