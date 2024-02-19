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
	currentLife = n;
	currentLife += n;
	if (currentLife > maxLife)
	{
		currentLife = maxLife;
	}
}

void LifeComponent::SetMax(int n)
{
	maxLife = n;
}

bool LifeComponent::Alive()
{
	return false;
}

void LifeComponent::AddLife(int n)
{
	currentLife += n;
	if (currentLife > maxLife)
		currentLife = maxLife;
}

void LifeComponent::RemoveLife(int n)
{
	currentLife -= n;
}

bool LifeComponent::Alive()
{
	return currentLife > 0;
}
