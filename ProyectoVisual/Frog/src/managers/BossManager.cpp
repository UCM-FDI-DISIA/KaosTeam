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
	attak->setContext(boss);
	franTrans = new TransformComponent(new Vector2D(0, 0), BOSS_W, BOSS_H);
	franTrans->setContext(boss);
	move = new MovementComponentFrançois();
	move->setContext(boss);
	detec = new ShadowDetection();
	detec->setContext(boss);

	shadow = &sdlutils().images().at("shadow");
	//SDL_SetTextureAlphaMod(shadow->getTexture(), );
	renderer = new RenderComponent(shadow, franTrans->getWidth());	
	boss->addComponent(ATTACK_COMPONENT,attak);
	boss->addComponent(MOVEMENT_COMPONENT, move);
	boss->addComponent(SHADOW_DETECTION, detec);
	boss->addComponent(TRANSFORM_COMPONENT, franTrans);	

	renderer->setContext(boss);
	renderer->initComponent();
	boss->addRenderComponent(renderer);
}

void BossManager::update()
{
}

void BossManager::render()
{
	boss->render();
}

void BossManager::changeDirection(int direction)
{
	move->changeDirection(direction);
}
