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
