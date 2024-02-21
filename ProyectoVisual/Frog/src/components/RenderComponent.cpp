#include "RenderComponent.h"

void RenderComponent::Render()
{
    SDL_Rect dest;
    dest.x = 20;//x * MAP_MULT;
    dest.y = 20;//y * MAP_MULT;
    dest.w = 100;//src.w * MAP_MULT;
    dest.h = 100;//src.h * MAP_MULT;

	myTexture->render(dest);
}
