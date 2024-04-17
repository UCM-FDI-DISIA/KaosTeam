#pragma once
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/AttackComponentFran�ois.h"
#include"../components/MovementComponentFran�ois.h"
#include "../components/ShadowDetection.h"
#include "../components/TransformComponent.h"
#include "../components/RenderComponent.h"


class BossManager
{
private:
	SDL_Rect shadowDest;
	Entity* boss;
	AttackComponentFran�ois* attak;
	TransformComponent* franTrans;
	MovementComponentFran�ois* move;
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