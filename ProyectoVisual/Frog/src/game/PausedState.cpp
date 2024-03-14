#include "PausedState.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/InputManager.h"
PausedState::PausedState() : imngr(im()) { };
void PausedState::enter()
{
	sdlutils().virtualTimer().pause();
}

void PausedState::leave()
{
	sdlutils().virtualTimer().resume();
}

void PausedState::update()
{
	if (imngr.getEscape())
	{

	}
}

