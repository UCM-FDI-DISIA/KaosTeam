#include "Component.h"

Component::Component() {
	initComponent();
}

void Component::setContext(Entity* ent) {
	this->ent = ent;
}
