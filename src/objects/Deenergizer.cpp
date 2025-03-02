#include "Deenergizer.h"
#include "AbstractComponent.h"
#include "GameGlobals.h"

Deenergizer::Deenergizer(AbstractGameObject *parent) :
	AbstractGameObject(parent)
{

}

void Deenergizer::activate()
{
	modifyComponent(MOD_Activate);
}

void Deenergizer::deactivate()
{
	modifyComponent(MOD_Deactivate);
}

void Deenergizer::reset()
{
	modifyComponent(MOD_Reset);
}

int Deenergizer::objectType() const
{
	return OBJ_Deenergizer;
}

void Deenergizer::modifyComponent(int type)
{
	auto *delaying{findComponent(BT_Delaying)};

	if (!delaying)
		return;

	switch (type) {
	case MOD_Activate:
		delaying->setEnabled(true);
		delaying->reset();
		break;
	case MOD_Deactivate:
		delaying->setEnabled(false);
		setPath(QPainterPath());
		break;
	case MOD_Reset:
		delaying->reset();
		break;
	}
}
