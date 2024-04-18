#pragma once

class ShopComponent;
class EntityShop
{
private:
	ShopComponent* myShopComponent=nullptr;
public:
	EntityShop();
	void addShopComponent(ShopComponent* sC); 
	virtual ~EntityShop();
	ShopComponent* getShopComponent() ;
};

