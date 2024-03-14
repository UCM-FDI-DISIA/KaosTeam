#include "RunningState.h"

#include "../scenes/RoomScene.h"

RunningState::RunningState(Game* game) : hud(new HUDManager(game, 9, 10, 0)), currScene(new RoomScene(1))
{
}

RunningState::~RunningState()
{
}

void RunningState::leave()
{
}

void RunningState::update()
{
}

void RunningState::enter()
{
}
