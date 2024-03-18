#include "DefenseComponent.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "RenderComponentFrog.h"

// faltan animaciones e implementarlo en el daño

void DefenseComponent::update()
{
	if (!otherStatesChecker() && auxInput->getAction4() && (DataManager::GetInstance()->getFrameTime() - timeSinceChange) > defenseCooldown)
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

bool DefenseComponent::getDefenseActive()	// getter de defenseActive para comprobar cuando reciba daño
{
	return defenseActive;
}

bool DefenseComponent::otherStatesChecker()	// comprueba que no haya otras acciones o estados en curso
{
	bool aux = false;

	if(defenseActive)	// añadir detector de ataque con lengua y ampliar si fuese necesario
	{
		aux = true;
	}

	return aux;
}