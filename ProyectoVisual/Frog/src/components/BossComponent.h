#pragma once

#include <vector>
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/TransformComponent.h"


const int MAX_TIME_ON_SHADOW = 3;
const int MAX_CUBIERTOS = 7;

enum bossState { MOVE, DETECT, ATTACK };
enum tipoCubierto { TENEDOR, CUCHILLO };
struct Cubierto {
	Entity* tipo;
	TransformComponent* tr;
	Texture* tex; //Imagen del cubierto (tenerdor o cuchillo)
	int spawnTime; //Tiempo en spawnear tras iniciar el ataque del Boss
};

class BossComponent: public Component
{	
private:
	bossState currState;
	std::vector<Cubierto*> cubiertos;
	std::vector<std::pair<Cubierto*, bool>> poolCubiertos; //El numero de cubiertos max instanciados depende de la zona

	int shadowTimer; //para saber cuanto tiempo ha pasado en la sombra
	int postAttackTimer; //para evitar que empiece a detectar tras un ataque

	float multiplier; //Se usa para reducir la velocidad de la sombra
	float speed; //Velocidad de la sombra
	Vector2D pos; //Posicion de la sombra
	Texture* sombra;
	TransformComponent* tr;

public:
	BossComponent();
	~BossComponent();

	void initComponent() override;
	void update() override;

	void move();
	void detect();
	void attack();

	void darkenShadow();
	void createCutlery(); //Crear cubiertos
	void moveCutlery(); //Mover cubiertos

	bool isFlonkOnShadow() const;
	bool hasCrashed() const; //Comprueba si un cubierto ha chocado contra otro objeto
	bool isOutOfScreen() const; //Comprueba si un cubierto se ha salido de la pantalla
};

