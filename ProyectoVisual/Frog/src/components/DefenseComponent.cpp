#include "DefenseComponent.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "RenderComponentFrog.h"

void DefenseComponent::update()
{
	if (!defenseActive && auxInput->getAction4())
	{
		
	}
	else if (defenseActive)
	{
		
	}
}

bool DefenseComponent::getDefenseActive()
{
	return defenseActive;
}