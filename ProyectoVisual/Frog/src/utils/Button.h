#pragma once
#include <functional>
#include "Vector2D.h"
#include "../sdlutils/Texture.h"

using callBack = std::function<void(void)>;
class Button
{
private:
	Texture* texture = nullptr;
	callBack callB;
	Vector2D position;
public:
	Button() {};
	~Button() {};
	Button(Texture* tex, Vector2D pos) :texture(tex), position(pos) {};
	Vector2D GetPosition() const { return position; }
	void connect(callBack call);
	void render();
	void perform();
};