#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
/*
* Clase que gestiona el componente para las entidades de la tienda
* Se encarga sobre todo de su renderizado (saber si esta seleccionado y asi gesrionar la opacidad)
y de saber si ha sido comprado
*/
class ShopComponent :public Component
{
private:
	bool buy;
	bool selected;
	Texture& texture;
	SDL_Rect textureRect;
	int uses;
public:
	ShopComponent(Texture& t, SDL_Rect rect, int u) :texture(t), buy(false),textureRect(rect),selected(false), uses(u) {
		texture.setAlphaMod(200);
	};
	~ShopComponent() {};
	bool isBuy() { return buy; }
	void setBuy() { 
		uses--;
		if(uses==0) buy = true;
	}
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
				texture.setAlphaMod(170);
		}
			
	}
};
