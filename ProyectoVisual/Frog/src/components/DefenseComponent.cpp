#include "DefenseComponent.h"
#include "../ecs/Entity.h"
#include "../managers/DataManager.h"
#include "RenderComponentFrog.h"


#include <iostream>

// faltan animaciones e implementarlo en el daño
// la idea es que cuando reciba daño se compruebe el defenseActive y si está activado no se recibe daño

DefenseComponent::DefenseComponent() : inputM(InputManager::GetInstance())
{
	defenseTime = 750;
	timeSinceChange = 1000;
	defenseCooldown = 750;
	defenseActive = false;

}

void DefenseComponent::update()
{
	if (!otherStatesChecker() && inputM->getAction1() && (DataManager::GetInstance()->getFrameTime() - timeSinceChange) > defenseCooldown)
	{
		defenseActive = true;
		timeSinceChange = DataManager::GetInstance()->getFrameTime();
	}
	else if (defenseActive && (DataManager::GetInstance()->getFrameTime() - timeSinceChange) > defenseTime)
	{
		defenseActive = false;
		timeSinceChange = DataManager::GetInstance()->getFrameTime();
	}

	std::cout << defenseActive;
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

void DefenseComponent::defendAnim()
{
	static_cast<RenderComponentFrog*>(ent->getRenderComponentFrog())->AttackStart(false);

}