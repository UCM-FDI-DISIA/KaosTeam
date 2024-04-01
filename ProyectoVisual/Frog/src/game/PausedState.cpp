#include "PausedState.h"
#include "../scenes/Menu.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/InputManager.h"
#include "../managers/HUDManager.h"
#include"Game.h"

PausedState::PausedState(Game* g) :game(g), imngr(im()), hudmngr(hud()),mPause(new Menu(g, this, 
	&sdlutils().images().at("BotonSeguirPausa"), &sdlutils().images().at("BotonSalirPausa"), INICIO))
{
}
PausedState::~PausedState()
{
	delete mPause;
}
;
void PausedState::enter() //Asi no deberia de ser el enter pero por ahora funcionara como el callback para continuar 
{
	sdlutils().virtualTimer().resume();
	game->changeGameState(game->RUNNING);
}

void PausedState::leave()
{
	sdlutils().virtualTimer().resume();
	game->changeGameState(game->NEWGAME);
}

void PausedState::update()
{
	if (imngr.getEscape())
	{
		game->changeGameState(game->RUNNING);
	}
}

