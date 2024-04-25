#pragma once
#include <functional>
#include "Vector2D.h"
#include "../sdlutils/Texture.h"

using callBack = std::function<void(void)>;
class Button
{
private:
	Texture* texture;
	callBack callB;
	SDL_Rect dest;
public:
	Button() {};
	~Button();
	Button(Texture* tex, SDL_Rect dst) :texture(tex), dest(dst) {};
	
	void connect(callBack call);
	void render();
	void perform();

	Texture* getTexture() const { return texture; }
	SDL_Rect getRect() const { return dest; }

};