#pragma once

class ShopComponent;
class EntityShop
{
private:
	ShopComponent* myShopComponent;
public:
	EntityShop();
	void addShopComponent(ShopComponent* sC); 
	virtual ~EntityShop();
	ShopComponent* getShopComponent() ;
};

