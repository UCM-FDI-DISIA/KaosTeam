#include"Button.h"

Button::~Button()
{
	texture = nullptr;
}

void Button::connect(callBack call)
{
	callB = call;
}

void Button::render()
{
	texture->render(dest);
}

void Button::perform()
{
	callB();
}
