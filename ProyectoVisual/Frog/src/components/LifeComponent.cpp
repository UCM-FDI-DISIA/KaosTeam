#include "LifeComponent.h"

int LifeComponent::GetActual()
{
	return vidaActual;
}

int LifeComponent::GetMax()
{
	return vidaMaxima;
}

void LifeComponent::SetActual(int n)
{
	vidaActual += n;
	if (vidaActual > vidaMaxima)
	{
		vidaActual = vidaMaxima;

	//Si ya no tiene vidas (lo compruebo aqui para no tener que hacerlo todo el rato en el update)
	if (!alive()) {
		animator->stopAnimation(); //Paramos la animaci�n que estuviese haciendo
		animator->playAnimation("DEATH"); //Reproducimos animacion de muerte (si la tiene)
		timerforDelete.resume(); //Ponemos contador en marcha
	}
}

void LifeComponent::SetMax(int n)
{
	vidaMaxima += n;
}

bool LifeComponent::alive()
{
	return vidaActual > 0;
}

void LifeComponent::hit(int damage) {
	vidaActual -= damage;
}