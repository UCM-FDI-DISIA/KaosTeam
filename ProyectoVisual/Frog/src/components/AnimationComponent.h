#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
/*
* Clase base abstracta del componente que gestiona las animaciones de un sprite de una entidad
*/

/*Información de la animación*/
struct Animation {
	std::vector<Vector2D> frames;
	bool flip;
	bool repeat;
	Animation(const std::vector<Vector2D>& f, bool fl, bool rep) {
		frames = f; flip = fl; repeat = rep;
	};
	Animation() {};
};

 /* Mapa de animaciones con su nombre y coordenadas de frames */
using Animations = std::unordered_map<std::string, Animation>;
const int FRAME_RATE = 10;
class Texture;

class AnimationComponent : public Component
{
protected:
	Texture* tex_;							// Textura
	float sc;								// Escala
	int x_, y_;								// Coordenadas x e y (Supongo que habria que leerlas de la posicion de la entidad)
	//int frameWidth_, frameHeight_;			// Ancho y Alto de un frame
	int nRow_, nCol_;						// Numero de filas y cols
	int currentFrameR_, currentFrameC_;		// Fila y Columna actual
	int finalFrameR_, finalFrameC_;			// Fila y Columna final de la animacion 
	int frameIndex_;
	int lastChange_;						// Ultimo refresh de animacion
	Animations animationSet_;				// Mapa de animaciones de la entidad
	Animation currentAnim_;                 // Animacion actual
	std::string currentAnimName_;
	//SDL_RendererFlip flip_;				// Flip
	bool isPlaying_;						// Bool que indica si ya se esta reproduciendo una animacion
	void updateAnimation(const Animation& currentAnim, int index);
	Animation getCurrentAnim() const { return currentAnim_; };
public:
	//AnimationComponent(std::string filename, int wframes, int hframes, float sc = 1);
	AnimationComponent(Texture* tex, int rows, int cols, float scale);
	void addAnimation(const std::string& name, const Animation& anim);
	void playAnimation(const std::string& name);
	virtual void render() {};
	void update() override;
};

