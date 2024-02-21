#include "MoneyComponent.h"

int MoneyComponent::GetMoney()
{
	return money;
}

void MoneyComponent::AddMoney(int n)
{
	money += n;
}

bool MoneyComponent::TakeMoney(int price)
{
	if (price>money)
	return false;

	money -= price;
	return true;
}
