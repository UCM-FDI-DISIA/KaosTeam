#include "AnimationComponent.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Component.h"
#include <SDL.h>


/* Constructor del animador */
AnimationComponent::AnimationComponent() :
	Component(),
	//x(ent->getX()),
	//y(ent->getY()),
	//sc(scale),
	//tex(tex),
    //nRow(rows),
	//nCol(cols),
	currentFrameR(0),
	currentFrameC(0),
	finalFrameR(0),
	finalFrameC(0),
	lastChange(0),
	frameIndex(0),
	isPlaying(false),
	currentAnimName(""),
	currentAnim() {}

/* Añade una animacion nueva al mapa */
void AnimationComponent::addAnimation(const std::string& name, const Animation& anim)
{
	//Insertamos en el mapa la lista de coordenadas
	animationSet[name] = anim;
}

/* Reproduce una animacion dado su nombre */
void AnimationComponent::playAnimation(const std::string& name)
{
	//Comprobamos si esta en el mapa y que no este reproduciendo otra animacion
	if (animationSet.find(name) != animationSet.end() && !isPlaying) {
		currentAnim = animationSet[name]; //Seteamos animacion actual
		currentAnimName = name;

		//Inicializamos inicio y final de la animacion
		currentFrameR = animationSet[name].frames.front().getX();
		currentFrameC = animationSet[name].frames.front().getY();

		finalFrameR = animationSet[name].frames.back().getX();
		finalFrameC = animationSet[name].frames.back().getY();

		isPlaying = true;
		frameIndex = 0;
	}	
}

void AnimationComponent::removeAnimations() {
	animationSet.clear();
}

void AnimationComponent::stopAnimation() {
	currentFrameR = currentFrameC = 0;
	finalFrameR = finalFrameC = 0,
	lastChange = 0;
	frameIndex = 0;
	isPlaying = false;
	currentAnimName = "";
}

/* Mueve al siguiente frame de animacion */
void AnimationComponent::updateAnimation(const Animation& currenAnim, int index)
{
	if (currentFrameC != finalFrameC || currentFrameR != finalFrameR){ //Actualizamos animacion
		currentFrameR = currenAnim.frames[index].getX();
		currentFrameC = currenAnim.frames[index].getY();
	}
	else if (currenAnim.repeat) { //si la anim es en bucle
		isPlaying = false;
		playAnimation(currentAnimName);
	}  
	else { //si no es en bucle -> volvemos a frame inicial
		isPlaying = false;
		currentFrameR = currenAnim.frames.front().getX();
		currentFrameC = currenAnim.frames.front().getY(); 
	}
}

/* Actualiza la animacion */
void AnimationComponent::update()
{
	if (sdlutils().virtualTimer().currTime() > lastChange+ (1000 / FRAME_RATE)) {
		lastChange = sdlutils().virtualTimer().currTime();
		if (isPlaying) {
			updateAnimation(currentAnim, frameIndex);
			frameIndex++;
		}
	}
}