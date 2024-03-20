#include "PausedState.h"
#include "../scenes/MenuPausa.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/InputManager.h"
#include "../managers/HUDManager.h"
#include"Game.h"

PausedState::PausedState(Game* game) :game(game), imngr(im()), hudmngr(hud()),mPause(new MenuPausa(game,this))
{
};
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
		game->changeGameState(game->RUNNING);
	}
}

