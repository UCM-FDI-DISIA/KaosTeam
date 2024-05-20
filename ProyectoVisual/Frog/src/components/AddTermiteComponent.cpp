#include "AddTermiteComponent.h"
#include "../managers/DataManager.h"
#include "../ecs/Entity.h"
#include "../scenes/RoomScene.h"

AddTermiteComponent::AddTermiteComponent(Vector2D pos): spawnPos(pos), lastTimeGenerated(DataManager::GetInstance()->getFrameTime())
{
}

void AddTermiteComponent::update()
{
	if ((DataManager::GetInstance()->getFrameTime() - lastTimeGenerated) > waitTime) {

		ent->getScene()->createTermita(spawnPos);
		lastTimeGenerated = DataManager::GetInstance()->getFrameTime();
	}
}
