#pragma once

#include <vector>
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"


const int MAX_TIME_ON_SHADOW = 3;
const int MAX_CUBIERTOS = 7;

enum bossState { MOVE, DETECT, ATTACK };
typedef int bossState;
struct Cubierto {
	Entity* tipo;
	TransformComponent* tr;
	Texture* tex;
};

class BossComponent: public Component
{	
private:
	bossState currState;
	std::vector<Cubierto*> cubiertos;
	std::vector<std::pair<Cubierto*, bool>> poolCubiertos;

	int shadowTimer; //para saber cuanto tiempo ha pasado en la sombra
	int postAttackTimer; //para evitar que empiece a detectar tras un ataque
	int speed; //velocidad de fracois

	TransformComponent* tr;
	Texture* sombra;
public:
	BossComponent();
	~BossComponent();

	void initComponent() override;
	void update() override;

	void move();
	void detect();
	void attack();

	void darkenShadow();

	bool isFlonkOnShadow() const;
};

