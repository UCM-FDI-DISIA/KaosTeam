#include "AnimationComponent.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Component.h"
#include <SDL.h>

//AnimationComponent::AnimationComponent(std::string filename, int rows, int cols, float sc) :
//	Component(),
//	x_(ent->getX()),
//	y_(ent->getY()),
//	sc(sc),
//	nRow_(rows),
//	nCol_(cols),
//	currentFrameR_(0),
//	currentFrameC_(0),
//	finalFrameR_(0),
//	finalFrameC_(0),
//	lastChange_(0),
//	frameIndex_(0),
//	isPlaying_(false),
//	currentAnimName_(""),
//	currentAnim_() {
//	tex_ = new Texture(sdlutils().renderer(), filename, rows, cols);
//}

/* Constructor del animador */
AnimationComponent::AnimationComponent(Texture* tex, int rows, int cols, float scale) :
	Component(),
	x_(ent->getX()),
	y_(ent->getY()),
	sc(scale),
	tex_(tex),
	nRow_(rows),
	nCol_(cols),
	currentFrameR_(0),
	currentFrameC_(0),
	finalFrameR_(0),
	finalFrameC_(0),
	lastChange_(0),
	frameIndex_(0),
	isPlaying_(false),
	currentAnimName_(""),
	currentAnim_() {}

/* Añade una animacion nueva al mapa */
void AnimationComponent::addAnimation(const std::string& name, const Animation& anim)
{
	//Insertamos en el mapa la lista de coordenadas
	animationSet_[name] = anim;
}

/* Reproduce una animacion dado su nombre */
void AnimationComponent::playAnimation(const std::string& name)
{
	//Comprobamos si esta en el mapa y que no este reproduciendo otra animacion
	if (animationSet_.find(name) != animationSet_.end() && !isPlaying_) {
		currentAnim_ = animationSet_[name]; //Seteamos animacion actual
		currentAnimName_ = name;

		//Inicializamos inicio y final de la animacion
		currentFrameR_ = animationSet_[name].frames.front().getX();
		currentFrameC_ = animationSet_[name].frames.front().getY();

		finalFrameR_ = animationSet_[name].frames.back().getX();
		finalFrameC_ = animationSet_[name].frames.back().getY();

		isPlaying_ = true;
		frameIndex_ = 0;
	}	
}

/* Mueve al siguiente frame de animacion */
void AnimationComponent::updateAnimation(const Animation& currenAnim, int index)
{
	if (currentFrameC_ != finalFrameC_ || currentFrameR_ != finalFrameR_){ //Actualizamos animacion
		currentFrameR_ = currenAnim.frames[index].getX();
		currentFrameC_ = currenAnim.frames[index].getY();
	}
	else if (currenAnim.repeat) { //si la anim es en bucle
		isPlaying_ = false;
		playAnimation(currentAnimName_);
	}  
	else { //si no es en bucle -> volvemos a frame inicial
		isPlaying_ = false;
		currentFrameR_ = currenAnim.frames.front().getX();
		currentFrameC_ = currenAnim.frames.front().getY(); 
	}
}

/* Renderiza el frame actual -> (Esto deberia hacerlo el renderComponent) */
/*void AnimationComponent::render()
{
	//Rect destino
	SDL_Rect dest = build_sdlrect(x_, y_, frameWidth_, frameHeight_);
	//Renderizamos con el metodo de Texture renderFrame
	tex_->renderFrame(dest, currentFrameR_, currentFrameC_);
}*/

/* Actualiza la animacion */
void AnimationComponent::update()
{
	if (sdlutils().virtualTimer().currTime() > lastChange_+ (1000 / FRAME_RATE)) {
		lastChange_ = sdlutils().virtualTimer().currTime();
		if (isPlaying_) {
			updateAnimation(currentAnim_, frameIndex_);
			frameIndex_++;
		}
	}
}