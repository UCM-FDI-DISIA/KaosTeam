#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
class ShopComponent :public Component
{
private:
	bool buy;
	bool selected;
	Texture& texture;
	SDL_Rect textureRect;
public:
	ShopComponent(Texture& t, SDL_Rect rect) :texture(t), buy(false),textureRect(rect),selected(false) {
		texture.setAlphaMod(200);
	};
	~ShopComponent() {};
	bool isBuy() { return buy; }
	void setBuy() { buy = true; }
	void quitSelectd() { selected = false; }
	void setSelected() { selected = true; }
	void myRender() { texture.render(textureRect); }
	void setOppacity() {
		if (buy)
			texture.setAlphaMod(0);
		else if (!buy) {
			if (selected)
				texture.setAlphaMod(255);
			else 
				texture.setAlphaMod(200);
		}
			
	}
};
