#include "DefenseComponent.h"
#include "../ecs/Entity.h"
#include "../managers/DataManager.h"
#include "RenderComponentFrog.h"


#include <iostream>

DefenseComponent::DefenseComponent() : inputM(InputManager::GetInstance())
{
	defenseTime = 750;
	timeSinceChange = 1000;
	defenseCooldown = 750;
	defenseActive = false;

}

void DefenseComponent::update()
{
	if (inputM->getAction1() && (DataManager::GetInstance()->getFrameTime() - timeSinceChange) > defenseCooldown)	// revisa si se ha dado la orden de usar el escudo y si el cooldown ha pasado
	{
		defenseActive = true;
		timeSinceChange = DataManager::GetInstance()->getFrameTime();
		static_cast<RenderComponentFrog*>(ent->getRenderComponentFrog())->DefenseStart();	// animacion
	}
	else if (defenseActive && (DataManager::GetInstance()->getFrameTime() - timeSinceChange) > defenseTime)			// revisa si el tiempo del escudo ha terminado 
	{
		defenseActive = false;
		timeSinceChange = DataManager::GetInstance()->getFrameTime();						
		static_cast<RenderComponentFrog*>(ent->getRenderComponentFrog())->IdleStart();		// animacion

	}
}

bool DefenseComponent::getDefenseActive()	// getter de defenseActive
{
	return defenseActive;
}