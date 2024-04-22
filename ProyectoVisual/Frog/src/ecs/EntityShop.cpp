#include "EntityShop.h"
EntityShop::EntityShop() : myShopComponent(nullptr) {

}
EntityShop::~EntityShop()
{
	delete myShopComponent;
	myShopComponent = nullptr;
}
ShopComponent* EntityShop::getShopComponent() 
{
	return myShopComponent;
}
void EntityShop::addShopComponent(ShopComponent* sC)
{
	myShopComponent = sC;
}