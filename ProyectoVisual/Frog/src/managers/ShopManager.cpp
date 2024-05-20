#include "ShopManager.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/InputManager.h"
#include "../sdlutils/Texture.h"
#include "../components/ShopComponent.h"
#include "../ecs/EntityShop.h"


Shop::Shop() : imngr(im()), grasshoperValue(10), waspValue(15), flyValue(15), centipedeValue(20),
							player(nullptr), playerHUD(nullptr), playerInventory(nullptr),selected(nullptr),
							grasshoperTex(sdlutils().images().at("grasshopperSheet")),
							waspTex(sdlutils().images().at("avispa")),
							flyTex(sdlutils().images().at("fly")),
							centipedeTex(sdlutils().images().at("ciempies")),
							pricesTex(sdlutils().images().at("precios")),
							birdTex(sdlutils().images().at("pajaroTienda")),
							inputTex(sdlutils().images().at("inputTienda"))

{
	selectedPowerUp = GRASSHOPER;
	actualDirection = RIGHT;
	selected = grasshoper;
	initShopEntitys();
	setOppacity();
	lastChangeTexture = sdlutils().virtualTimer().currTime();
}
Shop::~Shop() {

	for (auto& a : animals) {
		delete a;
		a = nullptr;
	}
	selected = nullptr;
	player = nullptr;
	playerHUD = nullptr;
	playerInventory = nullptr;

	std::cout << "SHOP DELETED" << std::endl;
}
//inicializa y coloca las entidades que podemos comprar
void Shop::initShopEntitys() {
	ShopComponent* gShop = new ShopComponent(grasshoperTex, SDL_Rect{ 0,230,80,80 }, 1);
	grasshoper->addShopComponent(gShop);
	animals.push_back(grasshoper);
	ShopComponent* wShop = new ShopComponent(waspTex, SDL_Rect{87,155,65, 65 }, 1);
	wasp->addShopComponent(wShop);
	animals.push_back(wasp);
	ShopComponent* fShop = new ShopComponent(flyTex, SDL_Rect{ 170,180,flyTex.width(), flyTex.height() }, 3);
	fly->addShopComponent(fShop);
	animals.push_back(fly);
	ShopComponent* cShop = new ShopComponent(centipedeTex, SDL_Rect{ 245,230,65, 65 }, 1);
	centipede->addShopComponent(cShop);
	animals.push_back(centipede);
}
void Shop::setPlayer(Entity* player_) {
	player = player_;
	playerInventory = dynamic_cast<InventoryComponent*>(player->getComponent(INVENTORY_COMPONENT));
}
void Shop::setHUD(HUDManager* hud) {
	playerHUD = hud;
}
//gestiona la entidad seleccionada
void Shop::setSelected() {
	ShopComponent* sC = selected->getShopComponent();
	sC->quitSelectd();
	switch (selectedPowerUp) {
	case Shop::GRASSHOPER:
	{
		ShopComponent* sC = grasshoper->getShopComponent();
		sC->setSelected();
		selected = grasshoper;
	}
	break;
	case Shop::WASP:
	{
		ShopComponent* sC = wasp->getShopComponent();
		sC->setSelected();
		selected = wasp;
	}
	break;
	case Shop::FLY:
	{
		ShopComponent* sC = fly->getShopComponent();
		sC->setSelected();
		selected = fly;
	}
	break;
	case Shop::CENTIPEDE:
	{
		ShopComponent* sC = centipede->getShopComponent();
		sC->setSelected();
		selected = centipede;
	}
	break;
	default:
		break;
	}
}
//gestiona la opacidad de las entidades
void Shop::setOppacity() {
	for (auto& a : animals) {
		ShopComponent* sC = a->getShopComponent();
		sC->setOppacity();
	}
}
//cambia la textura del dialogo del pajaro
void Shop::changeTexture() {
	if (change) {
		inputTex.setAlphaMod(255);
		pricesTex.setAlphaMod(0);
	}
	else {
		pricesTex.setAlphaMod(255);
		inputTex.setAlphaMod(0);
	}
}
void Shop::render() {
	for (auto& a : animals) {
		ShopComponent* sC = a->getShopComponent();
		sC->myRender();
	}
	birdTex.render(SDL_Rect{ 540,170,250, 250 });
	pricesTex.render(SDL_Rect{ 330,50,250, 250 });
	inputTex.render(SDL_Rect{ 330,50,250, 250 });
}
void Shop::update() {

	//cambia la textura del dialogo del pajaro cuando pasa un tiempo
	if (sdlutils().virtualTimer().currTime() > lastChangeTexture + CHANGE_TIME) {
		change = !change;
		changeTexture();
		lastChangeTexture = sdlutils().virtualTimer().currTime();
	}
	//acciones de comprar o cambiar el animal seleccionado
	if (imngr.getAction2())
	{ buyPowerUp(selectedPowerUp); }
	else if (imngr.getAction3()) { changeAnimal(RIGHT); }
	else if (imngr.getAction1()){ changeAnimal(LEFT); }

}
//este metodo se llamara cuando del input se reciba la tecla comprar y se pasa la mejora seleccionada en ese momento
void Shop::buyPowerUp(PowerUps powerUp) {
	bool buy = false;
	switch (powerUp) {
		case Shop::GRASSHOPER: 
		{	
			ShopComponent* sC = grasshoper->getShopComponent();
			if (!sC->isBuy() && playerInventory->TakeMoney(grasshoperValue)) {
				//activar salto largo
				playerInventory->mejoras.saltamontes += 1;
				sC->setBuy();
				
			}
			else {
				//algo de dialogo
			}
		}	
		break;
		case Shop::WASP:
		{
			ShopComponent* sC = wasp->getShopComponent();
			if (!sC->isBuy() && playerInventory->TakeMoney(waspValue)) {
				//aumentar da�o
				playerInventory->mejoras.avispas += 1;
				sC->setBuy();
			}
			else {
				//algo de dialogo
			}
		}
		break;
		case Shop::FLY:
		{
			ShopComponent* sC = fly->getShopComponent();
			if (!sC->isBuy() && playerInventory->TakeMoney(flyValue)) {
				//aumentar vida
				playerInventory->mejoras.moscas += 1;
				sC->setBuy();
			}
			else {
				//algo de dialogo
			}
		}
		break;
		case Shop::CENTIPEDE:
		{
			ShopComponent* sC = centipede->getShopComponent();
			if (!sC->isBuy() && playerInventory->TakeMoney(centipedeValue)) {
				//aumentar alcance lengua
				playerInventory->mejoras.ciempies += 1;
				sC->setBuy();
				
			}
			else {
				//algo de dialogo
			}
		}
		break;
		default:
			break;	
	}
	setOppacity();
}
//cambia el animal seleccionado dependiendo de la direccion 
void Shop::changeAnimal(Direction dir)
{
	int step = (dir == RIGHT) ? 1 : -1;
	int next = (static_cast<int>(selectedPowerUp) + step + TOTAL) % TOTAL;

	int numSteps = 0;
	while (animals[next]->getShopComponent()->isBuy()) {
		next = (next + step + TOTAL) % TOTAL;
		numSteps++;
		if (numSteps >= TOTAL) {
			return;
		}
	}
	selectedPowerUp = static_cast<PowerUps>(next);
	setSelected();
	setOppacity();
}
