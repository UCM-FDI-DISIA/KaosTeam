#include "AnimationComponent.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Component.h"
#include <SDL.h>

/* Constructor del animador */
AnimationComponent::AnimationComponent(std::string filename, int rows, int cols, int x, int y) :
	Component(),
	x_(x),
	y_(y),
	nRow_(rows),
	nCol_(cols),
	currentFrameR_(0),
	currentFrameC_(0),
	finalFrameR_(0),
	finalFrameC_(0),
	lastChange_(0),
	isPlaying_(false)
{
	//Creamos textura -> En el futuro habria que cabiar para que funcione con todas las entidades
	tex_ = new Texture(sdlutils().renderer(), filename, rows, cols);
	//Dimensiones de un frame
	frameWidth_ = tex_->width() / cols;
	frameHeight_ = tex_->height() / rows;
}

/* Añade una animacion nueva al mapa */
void AnimationComponent::addAnimation(const std::string& name, const std::vector<Vector2D>& coorFrames)
{
	//Insertamos en el mapa la lista de coordenadas
	animationSet_[name] = coorFrames;
}

/* Reproduce una animacion dado su nombre */
void AnimationComponent::playAnimation(const std::string& name)
{
	//Comprobamos si esta en el mapa y que no este reproduciendo otra animacion
	if (animationSet_.find(name) != animationSet_.end() && !isPlaying_) {
		//Iniacilizamos inicio y final de la animacion
		currentFrameR_ = animationSet_[name].front().getX();
		currentFrameC_ = animationSet_[name].front().getY();

		finalFrameR_ = animationSet_[name].back().getX();
		finalFrameC_ = animationSet_[name].back().getY();

		isPlaying_ = true;
	}	
}

/* Mueve al siguiente frame de animacion */
void AnimationComponent::updateAnimation()
{
	if (currentFrameC_ <= finalFrameC_ && currentFrameR_ <= finalFrameR_) {
		currentFrameC_ = (currentFrameC_ + 1) % nCol_;
		if (currentFrameC_ == 0) {
			currentFrameR_ = (currentFrameR_ + 1) % nRow_;
		}
	}
	else isPlaying_ = false;
}

/* Renderiza el frame actual */
void AnimationComponent::render()
{
	//Rect destino
	SDL_Rect dest = build_sdlrect(x_, y_, frameWidth_, frameHeight_);
	//Renderizamos con el metodo de Texture renderFrame
	tex_->renderFrame(dest, currentFrameR_, currentFrameC_);
}

/* Actualiza la animacion */
void AnimationComponent::update()
{
	if (sdlutils().virtualTimer().currTime() > lastChange_ + 500) {
		lastChange_ = sdlutils().virtualTimer().currTime();
		if (isPlaying_) 
			updateAnimation();
	}
}