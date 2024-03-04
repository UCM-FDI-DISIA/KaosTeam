#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
/*
* Clase base abstracta del componente que gestiona las animaciones de un sprite de una entidad
*/
 /* Mapa de animaciones con su nombre y coordenadas de frames */
using Animations = std::unordered_map<std::string, std::vector<Vector2D>>;

class Texture;
class AnimationComponent : public Component
{
private:
	Texture* tex_;							// Textura
	int x_, y_;								// Coordenadas x e y (Supongo que habria que leerlas de la posicion de la entidad)
	int frameWidth_, frameHeight_;			// Ancho y Alto de un frame
	int nRow_, nCol_;						// Numero de filas y cols
	int currentFrameR_, currentFrameC_;		// Fila y Columna actual
	int finalFrameR_, finalFrameC_;			// Fila y Columna final de la animacion 
	int lastChange_;						// Ultimo refresh de animacion
	Animations animationSet_;				// Mapa de animaciones de la entidad
	//SDL_RendererFlip flip_;					// Flip
	bool isPlaying_;						// Bool que indica si ya se esta reproduciendo una animacion
public:
	AnimationComponent(std::string filename, int rows, int cols, int x, int y);
	void addAnimation(const std::string& name, const std::vector<Vector2D>& coorFrames);
	void playAnimation(const std::string& name);
	void updateAnimation();
	void render() override;
	void update() override;
};

