#include"Button.h"

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
