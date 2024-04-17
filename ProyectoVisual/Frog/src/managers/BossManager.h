#pragma once
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/AttackComponentFrançois.h"
#include"../components/MovementComponentFrançois.h"
#include "../components/ShadowDetection.h"
#include "../components/TransformComponent.h"
#include "../components/RenderComponent.h"


class BossManager
{
private:
	SDL_Rect shadowDest;
	Entity* boss;
	AttackComponentFrançois* attak;
	TransformComponent* franTrans;
	MovementComponentFrançois* move;
	ShadowDetection* detec;
	RenderComponent* renderer;
	Texture* shadow;
public:
	BossManager(Entity* fran);
	~BossManager();
	void init();
	void update();
	void render();
	void changeDirection(int direction);
};