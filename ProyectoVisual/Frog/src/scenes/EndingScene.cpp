#include "EndingScene.h"
#include "../managers/InputManager.h"
#include "../sdlutils/Texture.h"
#include "../managers/InputManager.h"
#include "../game/GameState.h"

EndingScene::EndingScene(GameState* nGS):game(Game::instance()),currBg(0), imngr(im()), initTime(sdlutils().virtualTimer().currTime()), gameState(nGS)
{
	bgDest.x = bgDest.y = 0;
	bgDest.w = WIN_WIDTH;
	bgDest.h = WIN_HEIGHT;

	bgs.reserve(NUM_TEXT);
	bgs.emplace_back(&sdlutils().images().at("Ending0"));
	bgs.emplace_back(&sdlutils().images().at("Ending1"));
	bgs.emplace_back(&sdlutils().images().at("Ending2"));
	bgs.emplace_back(&sdlutils().images().at("Ending3"));

}

void EndingScene::changeInitTime()
{
	initTime = sdlutils().virtualTimer().currTime();
}

EndingScene::~EndingScene()
{
}

void EndingScene::render()
{
	bgs[currBg]->render(bgDest);
}

void EndingScene::update()
{
	if (sdlutils().virtualTimer().currTime() - initTime>TRANSITION_TIME)
	{
		if (currBg + 1 == NUM_TEXT)
		{
			gameState->leave();
		}
		else
		{
			currBg++;
			initTime = sdlutils().virtualTimer().currTime();
		}

	}

}
