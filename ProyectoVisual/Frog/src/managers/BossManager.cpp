#include "BossManager.h"
#include "../utils/Vector2D.h"

BossManager::BossManager(Entity* fran):boss(fran), shadow(nullptr)
{
	init();
}

BossManager::~BossManager()
{
	delete boss;
	delete attak;
	delete franTrans;
	delete move;
	delete detec;
	delete renderer;
}

void BossManager::init()
{
	attak = new AttackComponentFrançois();
	franTrans = new TransformComponent(new Vector2D(0, 0), BOSS_W, BOSS_H);
	move = new MovementComponentFrançois(franTrans);
	detec = new ShadowDetection();

	shadow = &sdlutils().images().at("shadow");
	SDL_SetTextureAlphaMod(shadow->getTexture(), 3);
	renderer = new RenderComponent(shadow, franTrans->getWidth());	
	boss->addComponent(ATTACK_COMPONENT,attak);
	boss->addComponent(MOVEMENT_COMPONENT, move);
	boss->addComponent(SHADOW_DETECTION, detec);
	boss->addComponent(TRANSFORM_COMPONENT, franTrans);
	boss->addComponent(RENDER_COMPONENT, renderer);
}

void BossManager::update()
{
}

void BossManager::render()
{
	//boss->render();
}

void BossManager::changeDirection(int direction)
{
	move->changeDirection(direction);
}
