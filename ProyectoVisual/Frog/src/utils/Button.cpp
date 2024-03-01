#include"Button.h"

void Button::connect(callBack call)
{
	callB = call;
}

void Button::render()
{
	texture->render(position.getX(), position.getY());
}

void Button::perform()
{
	callB();
}
