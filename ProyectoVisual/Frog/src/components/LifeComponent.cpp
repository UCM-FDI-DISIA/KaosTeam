#include "LifeComponent.h"

int LifeComponent::GetCurrent()
{
	return currentLife;
}

int LifeComponent::GetMax()
{
	return maxLife;
}

void LifeComponent::SetActual(int n)
{
	currentLife += n;
	if (currentLife > maxLife)
	{
		currentLife = maxLife;
	}
}

void LifeComponent::SetMax(int n)
{
	maxLife += n;
}

bool LifeComponent::alive()
{
	return currentLife > 0;
}
