#include "DefenseComponent.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/DataManager.h"
#include "RenderComponentFrog.h"

void DefenseComponent::update()
{
	if (!defenseActive)
	{

	}
}

bool DefenseComponent::defenseActive()
{
	return defenseActive;
}