#include "EntityShop.h"
EntityShop::EntityShop() : myShopComponent(nullptr) {

}
EntityShop::~EntityShop()
{
	//myShopComponent = nullptr;
	delete myShopComponent;
}
ShopComponent* EntityShop::getShopComponent() 
{
	return myShopComponent;
}
void EntityShop::addShopComponent(ShopComponent* sC)
{
	myShopComponent = sC;
}