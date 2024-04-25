#include "DataManager.h"

//DataManager* DataManager::instance = nullptr;
std::unique_ptr<DataManager> DataManager::instance;

void DataManager::UpdateFrameTime() {
	frameTime = SDL_GetTicks();
}

Uint32 DataManager::getFrameTime() {
	return frameTime;
}

std::vector<bool> DataManager::getInteractObj(const std::string& path)
{
	if (interactedObjects.find(path) == interactedObjects.end())
		return {};
	else
		return interactedObjects[path];
}

void DataManager::addObjs(const std::string& path, const std::vector<bool>& interactObj)
{
	interactedObjects[path] = interactObj;
}

