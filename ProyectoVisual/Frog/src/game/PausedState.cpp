#include "PausedState.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/InputManager.h"
#include "../managers/HUDManager.h"

PausedState::PausedState(HUDManager* hud_, Scene& bg_, Scene& pause_) : imngr(im()), hud(hud_),
bgScene(bg_), mPause(pause_){};
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

