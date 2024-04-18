#include "EntityShop.h"
EntityShop::EntityShop() {

}
EntityShop::~EntityShop()
{
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