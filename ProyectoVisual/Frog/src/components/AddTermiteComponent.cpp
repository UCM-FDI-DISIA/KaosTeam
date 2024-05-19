#include "AddTermiteComponent.h"
#include "../managers/DataManager.h"
#include "../ecs/Entity.h"
#include "../scenes/RoomScene.h"

void AddTermiteComponent::update()
{
	if ((DataManager::GetInstance()->getFrameTime() - lastTimeGenerated) > waitTime) {

		ent->getScene()->AddEntity(ent->getScene()->createTermita(spawnPos));
	}
}
