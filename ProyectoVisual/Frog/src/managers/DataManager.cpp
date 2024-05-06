#include "DataManager.h"

//DataManager* DataManager::instance = nullptr;
std::unique_ptr<DataManager> DataManager::instance;

void DataManager::UpdateFrameTime() {
	frameTime = SDL_GetTicks();
}

Uint32 DataManager::getFrameTime() {
	return frameTime;
}

std::vector<ObjEdit>& DataManager::getInteractObj(std::string path)
{
	if (interactedObjects.find(path) == interactedObjects.end()) {
		std::vector<ObjEdit> interactObj(0, { false, {0,0} });
		return interactObj;
	}
	else
		return interactedObjects[path];
}

void DataManager::addObjs(const std::string& path, const std::vector<ObjEdit>& interactObj)
{
	interactedObjects[path] = interactObj;
}

