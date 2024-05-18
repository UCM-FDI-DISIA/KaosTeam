#pragma once

/*
* Son las entidades que se encuentran en la tienda para poder comprarse
*/
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

