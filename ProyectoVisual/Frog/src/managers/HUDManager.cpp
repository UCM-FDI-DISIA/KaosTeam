#include "HUDManager.h"
#include "../sdlutils/SDLUtils.h"


void
HUDManager::render()
{
	int i = 0;
	rect->x = xInicial;
	//vidas enteras
	for (i; i < vidasActuales-1; i += 2)
	{
		text->renderFrame(*rect, 0, 0);
		rect->x += rect->w;
	}
	//medias vidas
	if (vidasActuales % 2 != 0)
	{
		text->renderFrame(*rect, 0, 1);
		rect->x += rect->w;
		i += 2;
	}
	//vidas vacias
	for (i; i < vidasMax; i += 2)
	{
		text->renderFrame(*rect, 0, 2);
		rect->x += rect->w;
	}
}

HUDManager::HUDManager(Game* g, int vidasActuales, int VidasMaximas) : game(g), vidasActuales(vidasActuales), vidasMax(VidasMaximas), rect(new SDL_Rect())
{
	text = new Texture(sdlutils().renderer(), "resources/Sprites/moscaVidaSpritesheet.png", 1, 3);
	rect->y = yInicial;
	rect->w = text->width() / text->getCol();
	rect->h = text->height() / text->getRow();
}