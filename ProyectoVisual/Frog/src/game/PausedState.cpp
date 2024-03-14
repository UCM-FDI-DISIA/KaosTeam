#include "PausedState.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/InputManager.h"
PausedState::PausedState() : Scene(false), imngr(im()) { };
void PausedState::enter()
{
	sdlutils().virtualTimer().pause();
}

void PausedState::leave()
{
	sdlutils().virtualTimer().pause();
}

void PausedState::update()
{

}
