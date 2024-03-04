#include "DataManager.h"

DataManager* DataManager::instance = nullptr;

void DataManager::UpdateFrameTime() {
	frameTime = SDL_GetTicks();
}

Uint32 DataManager::getFrameTime() {
	return frameTime;
}